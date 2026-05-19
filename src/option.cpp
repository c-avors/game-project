#include "../include/option.h"

Option::Option(const std::string& text, float xPos, float yPos, const sf::Font& font, std::function<void()> callback, unsigned int textSize, sf::Color textColor)
    : textElement(font), action(callback){
    textElement.setFont(font);
    textElement.setString(text);
    textElement.setCharacterSize(textSize);
    textElement.setFillColor(textColor);
    textElement.setPosition({xPos, yPos});
}

void Option::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(textElement, states);
}

void Option::trigger() const {
    if (action) {
        action();
    }
}

void Option::setHighlight(bool isHighlighted) {
    if (isHighlighted) {
        textElement.setOutlineColor(sf::Color::Yellow);
        textElement.setOutlineThickness(3);
    } else {
        textElement.setOutlineThickness(0);
    }
}

sf::FloatRect Option::getGlobalBounds() const {
    return textElement.getGlobalBounds();
}