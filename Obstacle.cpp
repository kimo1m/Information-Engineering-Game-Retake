#include "Obstacle.hpp"

Obstacle::Obstacle(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color) {
    rectangle.setSize(size);
    rectangle.setFillColor(color);
    rectangle.setPosition(position);
}

void Obstacle::update(float deltaTime) {
    // Obstacles are static, so no update needed
}

void Obstacle::draw(sf::RenderWindow& window) {
    window.draw(rectangle);
}

sf::FloatRect Obstacle::getBounds() const {
    return rectangle.getGlobalBounds();
}

sf::Vector2f Obstacle::getPosition() const {
    return rectangle.getPosition();
}

void Obstacle::setPosition(const sf::Vector2f& position) {
    rectangle.setPosition(position);
}
