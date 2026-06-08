#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include <any>

class Option : public sf::Drawable {
private:
    sf::Text textElement;
    std::function<void()> action;
    

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Option(const std::string& text, float xPos, float yPos, const sf::Font& font, std::function<void()> callback, unsigned int textSize = 24, sf::Color textColor = sf::Color::White);

    void trigger() const;

    void setName(const std::string& text);
    void setHighlight(bool isHighlighted);
    void setTextPosition(sf::Vector2f position);
    
    // Checks option's bounds
    sf::FloatRect getGlobalBounds() const;
};