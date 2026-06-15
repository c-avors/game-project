#include "../include/animationManager.h"
#include <iostream>

AnimationManager::AnimationManager(AssetManager& am) : assetManager(am) {}

void AnimationManager::play(std::string move, sf::Vector2f position, float duration) {
    if (currentlyPlaying) return; // Prevent multiple triggers
    currentlyPlaying = true;
    const sf::Texture& tex = assetManager.getTexture(move);
    int frames = 18;
    if(move != "Veil") {
        frames = tex.getSize().x/450;
    }
    
    AttackAnimation newAnim(tex, frames, duration);
    newAnim.start(position);
    activeAnimations.push_back(newAnim);
}

void AnimationManager::update(float dt) {
    for (auto& anim : activeAnimations) {
        anim.update(dt);
    }

    // Remove animations that finished
    activeAnimations.erase(
        std::remove_if(activeAnimations.begin(), activeAnimations.end(),
        [](const AttackAnimation& a) { return !a.isActive(); }),
        activeAnimations.end()
    );
    if (activeAnimations.empty()) {
        currentlyPlaying = false;
    }
}

void AnimationManager::draw(sf::RenderWindow& window) {
    for (const auto& anim : activeAnimations) {
        anim.draw(window);
    }
}

bool AnimationManager::isAnimating() const {
    return !activeAnimations.empty();
}