// AudioManager.hpp
#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <SFML/Audio.hpp>
#include <string>

class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    // Loads and plays background music
    void playBackgroundMusic(const std::string& filePath);

    // Stops the background music
    void stopBackgroundMusic();

    // Pauses the background music
    void pauseBackgroundMusic();

    // Resumes the background music
    void resumeBackgroundMusic();

private:
    sf::Music backgroundMusic;
};

#endif // AUDIOMANAGER_HPP
