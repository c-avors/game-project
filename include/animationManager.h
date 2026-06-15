#include <vector>
#include <memory>
#include <algorithm>
#include "attackAnimation.h"
#include "assetsManager.h" // To get the textures

class AnimationManager {
private:
    std::vector<AttackAnimation> activeAnimations;
    AssetManager& assetManager; // Reference to your existing asset manager
    bool currentlyPlaying;

public:
    AnimationManager(AssetManager& am);
    void play(std::string move, sf::Vector2f position, float duration);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    bool isAnimating() const;
};