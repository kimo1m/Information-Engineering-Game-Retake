#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "GameObject.hpp"
#include <SFML/Graphics.hpp>

class Obstacle : public GameObject {
private:
    sf::RectangleShape rectangle;

public:
    Obstacle(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition() const override;
    void setPosition(const sf::Vector2f& position) override;
};

#endif // OBSTACLE_HPP
