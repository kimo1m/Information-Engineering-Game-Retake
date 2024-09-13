#ifndef VILLAIN_HPP
#define VILLAIN_HPP

#include "GameObject.hpp"
#include "Hero.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class Hero;

class Villain : public GameObject {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    sf::Vector2f direction;
    std::shared_ptr<Hero> hero;

public:
    Villain(const std::string& textureFile, const sf::Vector2f& startPos, std::shared_ptr<Hero> heroPtr);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition() const override;
    void setPosition(const sf::Vector2f& position) override;

private:
    void updateDirection();
};

#endif // VILLAIN_HPP
