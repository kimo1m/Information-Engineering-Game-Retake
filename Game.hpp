#ifndef GAME_HPP
#define GAME_HPP

#include "GameObject.hpp"
#include "Hero.hpp"
#include "Sword.hpp"
#include "Villain.hpp"
#include "Obstacle.hpp"
#include "AudioManager.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Game {
private:
    sf::RenderWindow window;
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    std::shared_ptr<Hero> hero;
    std::shared_ptr<Sword> sword;
    int score;
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;
    sf::Clock villainSpawnClock;
    bool gameOver;
    AudioManager audioManager;

    std::vector<std::shared_ptr<Obstacle>> obstacles;

public:
    Game();
    void run();
    void addGameObject(const std::shared_ptr<GameObject>& object);
    void setHero(const std::shared_ptr<Hero>& heroObj);
    void setSword(const std::shared_ptr<Sword>& swordObj);

private:
    void processEvents();
    void update(float deltaTime);
    void checkCollisions();
    void handleCollisionsWithObstacles();
    void resolveCollision(std::shared_ptr<GameObject> obj, std::shared_ptr<Obstacle> obstacle);
    void spawnVillain();
    void initializeObstacles();
    void render();
};

#endif // GAME_HPP
