#ifndef HERO_HPP
#define HERO_HPP

#include "GameObject.hpp"
#include "AnimatedSprite.hpp"
#include <memory>

class Hero : public GameObject {
private:
    std::shared_ptr<AnimatedSprite> sprite;
    float speed;

public:
    Hero(const std::string& textureFile);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition() const override;
    void setPosition(const sf::Vector2f& position) override;
};

#endif // HERO_HPP
