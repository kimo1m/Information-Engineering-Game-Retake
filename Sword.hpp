#ifndef SWORD_HPP
#define SWORD_HPP

#include "GameObject.hpp"
#include "Hero.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class Hero;

class Sword : public GameObject {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    std::shared_ptr<Hero> hero;

public:
    Sword(const std::string& textureFile, std::shared_ptr<Hero> heroPtr);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition() const override;
    void setPosition(const sf::Vector2f& position) override;

private:
    void updatePosition();
};

#endif // SWORD_HPP
