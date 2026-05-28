#include "../include/assetsManager.h"
#include <iostream>

void AssetManager::loadTexture(const std::string &name, const std::string &fileName){
    auto it = _textures.find(fileName);
    
    if (it != _textures.end()) {
        std::cerr << "Texture already loaded"<< std::endl;
    }
    sf::Texture tex;
    if (tex.loadFromFile(fileName)) {
        this->_textures[name] = tex;
    }
    
}

const sf::Texture& AssetManager::getTexture(const std::string &name) {
    return this->_textures.at(name);
}

void AssetManager::loadFont(const std::string &name, const std::string &fileName){
    sf::Font font;
    if (font.openFromFile(fileName)) {
        this->_fonts[name] = font;
    }
}

sf::Font& AssetManager::getFont(const std::string &name) {
    return this->_fonts.at(name);
}

void AssetManager::clearUnusedAssets() {
    _textures.clear();
}
