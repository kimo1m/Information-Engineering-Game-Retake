// AudioManager.cpp
#include "AudioManager.hpp"
#include <iostream>

AudioManager::AudioManager() {
    // Constructor: Initialize or configure if needed
}

AudioManager::~AudioManager() {
    // Destructor: Cleanup if needed
}

void AudioManager::playBackgroundMusic(const std::string& filePath) {
    if (!backgroundMusic.openFromFile(filePath)) {
        std::cerr << "Failed to load music file: " << filePath << std::endl;
        return;
    }
    backgroundMusic.setLoop(true); // Loop the background music
    backgroundMusic.play();
}

void AudioManager::stopBackgroundMusic() {
    backgroundMusic.stop();
}

void AudioManager::pauseBackgroundMusic() {
    backgroundMusic.pause();
}

void AudioManager::resumeBackgroundMusic() {
    backgroundMusic.play();
}
