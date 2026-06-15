#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <functional>
#include "enum.h"

class AttackAnimation {
private:
    sf::Sprite sprite;
    float timer = 0.0f;
    int currentFrame = 0;
    bool active = false;

    // Configuration
    float frameDuration = 0.1f;
    int totalFrames = 8;

public:
    AttackAnimation( const sf::Texture& texture, int frames = 18, float duration = 0.8f);
    void start(sf::Vector2f position);
    void update(float dt);
    bool isActive() const;
    void draw(sf::RenderWindow& window) const;
};