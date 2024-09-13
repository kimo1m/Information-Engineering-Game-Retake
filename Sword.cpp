#include "Sword.hpp"
#include <iostream>

Sword::Sword(const std::string& textureFile, std::shared_ptr<Hero> heroPtr) : hero(heroPtr) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Failed to load sword texture!" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setScale(0.05f, 0.05f);
    updatePosition();
}

void Sword::update(float deltaTime) {
    updatePosition();
}

void Sword::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Sword::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Sword::getPosition() const {
    return sprite.getPosition();
}

void Sword::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

void Sword::updatePosition() {
    if (hero) {
        sf::Vector2f heroPos = hero->getPosition();
        sprite.setPosition(heroPos.x + hero->getBounds().width, heroPos.y + hero->getBounds().height / 2.f - sprite.getGlobalBounds().height / 2.f);
    }
}
