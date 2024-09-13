#include "AnimatedSprite.hpp"
#include <iostream>

AnimatedSprite::AnimatedSprite(float fps, const std::string& textureFile)
    : frameRate(fps), timeSinceLastFrame(0.f), currentFrame(0) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Failed to load texture!" << std::endl;
    }
    setTexture(texture);
}

void AnimatedSprite::addAnimationFrame(const sf::IntRect& frame) {
    frames.push_back(frame);
    if (frames.size() == 1) { // Set the initial frame if this is the first frame
        setTextureRect(frames[0]);
    }
}

void AnimatedSprite::update(float deltaTime) {
    if (frames.empty()) {
        return; // No frames to animate
    }

    timeSinceLastFrame += deltaTime;
    if (timeSinceLastFrame >= 1.f / frameRate) {
        timeSinceLastFrame = 0.f;
        currentFrame = (currentFrame + 1) % frames.size();
        setTextureRect(frames[currentFrame]);
    }
}

void AnimatedSprite::setAnimationFrames(const std::vector<sf::IntRect>& animationFrames) {
    frames = animationFrames;
    if (!frames.empty()) {
        setTextureRect(frames[0]);
    }
}
