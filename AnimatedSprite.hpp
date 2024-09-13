#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class AnimatedSprite : public sf::Sprite {
private:
    sf::Texture texture;
    std::vector<sf::IntRect> frames;
    float frameRate; // Frames per second
    float timeSinceLastFrame;
    int currentFrame;

public:
    AnimatedSprite(float fps, const std::string& textureFile);
    void addAnimationFrame(const sf::IntRect& frame);
    void update(float deltaTime);
    void setAnimationFrames(const std::vector<sf::IntRect>& animationFrames);
};

#endif // ANIMATEDSPRITE_HPP
