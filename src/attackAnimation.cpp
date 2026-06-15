#include "../include/attackAnimation.h"
#include <iostream>

AttackAnimation::AttackAnimation(const sf::Texture& texture, int frames, float duration) : sprite(texture), frameDuration(duration / frames), timer(0.0f), currentFrame(0), totalFrames(frames), active(false) {}

bool AttackAnimation::isActive() const {
    return active;
}

void AttackAnimation::update(float dt) {
    if (!active) return;
    
    timer += dt;
    if (timer >= frameDuration) {
        timer = 0;
        currentFrame++;
        if (currentFrame >= totalFrames) {
            active = false;
        } else {
            int frameWidth = sprite.getTexture().getSize().x / totalFrames;
            int frameHeight = sprite.getTexture().getSize().y;
            sprite.setTextureRect(sf::IntRect({currentFrame * frameWidth, 0}, {frameWidth, frameHeight}));
        }
    }
}

void AttackAnimation::draw(sf::RenderWindow& window) const {
    if (active) window.draw(sprite);
}

void AttackAnimation::start(sf::Vector2f position) {
        sprite.setPosition(position);
        active = true;
        currentFrame = 0;
        timer = 0.0f;
    }