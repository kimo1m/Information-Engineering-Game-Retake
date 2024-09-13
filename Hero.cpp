#include "Hero.hpp"
#include <SFML/Graphics.hpp>

Hero::Hero(const std::string& textureFile) {
    sprite = std::make_shared<AnimatedSprite>(10.0f, textureFile);

    // Define animation frames
    sprite->addAnimationFrame(sf::IntRect(0, 0, 50, 37));  // Hero standing frame 1
    sprite->addAnimationFrame(sf::IntRect(50, 0, 50, 37)); // Hero standing frame 2
    sprite->addAnimationFrame(sf::IntRect(100, 0, 50, 37)); // Hero standing frame 3
    sprite->addAnimationFrame(sf::IntRect(150, 0, 50, 37)); // Hero running frame 1
    sprite->addAnimationFrame(sf::IntRect(200, 0, 50, 37)); // Hero running frame 2
    sprite->addAnimationFrame(sf::IntRect(250, 0, 50, 37)); // Hero running frame 3
    sprite->addAnimationFrame(sf::IntRect(300, 0, 50, 37)); // Hero running frame 4
    sprite->addAnimationFrame(sf::IntRect(350, 0, 50, 37)); // Hero running frame 5
    sprite->addAnimationFrame(sf::IntRect(400, 0, 50, 37)); // Hero running frame 6

    sprite->setPosition(400.f, 300.f);
    speed = 200.f;
}

void Hero::update(float deltaTime) {
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        movement.x -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        movement.x += speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        movement.y -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        movement.y += speed * deltaTime;

    sprite->move(movement);

    // Keep hero within window bounds
    sf::Vector2u windowSize = { 800, 600 };
    sf::Vector2f heroPos = sprite->getPosition();
    if (heroPos.x < 0) heroPos.x = 0;
    if (heroPos.y < 0) heroPos.y = 0;
    if (heroPos.x + sprite->getGlobalBounds().width > windowSize.x) heroPos.x = windowSize.x - sprite->getGlobalBounds().width;
    if (heroPos.y + sprite->getGlobalBounds().height > windowSize.y) heroPos.y = windowSize.y - sprite->getGlobalBounds().height;
    sprite->setPosition(heroPos);

    sprite->update(deltaTime); // Update the animation
}

void Hero::draw(sf::RenderWindow& window) {
    window.draw(*sprite);
}

sf::FloatRect Hero::getBounds() const {
    return sprite->getGlobalBounds();
}

sf::Vector2f Hero::getPosition() const {
    return sprite->getPosition();
}

void Hero::setPosition(const sf::Vector2f& position) {
    sprite->setPosition(position);
}
