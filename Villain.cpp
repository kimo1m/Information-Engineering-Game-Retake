#include "Villain.hpp"
#include <cmath>
#include <iostream>

Villain::Villain(const std::string& textureFile, const sf::Vector2f& startPos, std::shared_ptr<Hero> heroPtr)
    : hero(heroPtr) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Failed to load villain texture!" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setScale(0.05f, 0.05f);  // Set the scale for villains
    sprite.setPosition(startPos);
    speed = 100.f;
    updateDirection();
}

void Villain::update(float deltaTime) {
    if (hero) {
        updateDirection();
        sprite.move(direction * speed * deltaTime);
    }
}

void Villain::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Villain::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Villain::getPosition() const {
    return sprite.getPosition();
}

void Villain::setPosition(const sf::Vector2f& position) {
    sprite.setPosition(position);
}

void Villain::updateDirection() {
    if (hero) {
        sf::Vector2f heroPos = hero->getPosition();
        sf::Vector2f currentPos = sprite.getPosition();
        direction = heroPos - currentPos;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) {
            direction /= length;
        }
    }
}
