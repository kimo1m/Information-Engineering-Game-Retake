#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game() : window(sf::VideoMode(800, 600), "2D Game"), score(0), gameOver(false) {
    if (!font.loadFromFile("BebasNeue-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);

    sf::Vector2u windowSize = window.getSize();
    gameOverText.setPosition(windowSize.x / 2.f - gameOverText.getGlobalBounds().width / 2.f, windowSize.y / 2.f - gameOverText.getGlobalBounds().height / 2.f);

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Initialize obstacles
    initializeObstacles();

    // Initialize hero and sword
    std::shared_ptr<Hero> heroObj = std::make_shared<Hero>("animation.png");
    setHero(heroObj);

    std::shared_ptr<Sword> swordObj = std::make_shared<Sword>("sword.png", heroObj);
    setSword(swordObj);

    // Initialize audio
    audioManager.playBackgroundMusic("background_audio.mp3");

}

void Game::addGameObject(const std::shared_ptr<GameObject>& object) {
    gameObjects.push_back(object);
}

void Game::setHero(const std::shared_ptr<Hero>& heroObj) {
    hero = heroObj;
    addGameObject(hero);
}

void Game::setSword(const std::shared_ptr<Sword>& swordObj) {
    sword = swordObj;
    addGameObject(sword);
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        if (!gameOver) {
            update(deltaTime.asSeconds());
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(float deltaTime) {
    if (!gameOver) {
        for (auto& obj : gameObjects) {
            obj->update(deltaTime);
        }

        // Spawn villains periodically
        if (villainSpawnClock.getElapsedTime().asSeconds() > 4.f) {
            spawnVillain();
            villainSpawnClock.restart();
        }

        checkCollisions();
        handleCollisionsWithObstacles();

        scoreText.setString("Score: " + std::to_string(score));
    }
}

void Game::checkCollisions() {
    if (hero && sword) {
        for (auto it = gameObjects.begin(); it != gameObjects.end(); ) {
            if (auto villain = std::dynamic_pointer_cast<Villain>(*it)) {
                if (sword->getBounds().intersects(villain->getBounds())) {
                    // Remove the villain and increase the score
                    it = gameObjects.erase(it);
                    score++;
                }
                else {
                    ++it;
                }
            }
            else {
                ++it;
            }
        }

        // Check if hero collides with any villains
        for (const auto& obj : gameObjects) {
            if (auto villain = std::dynamic_pointer_cast<Villain>(obj)) {
                if (villain->getBounds().intersects(hero->getBounds())) {
                    gameOver = true;
                    gameOverText.setString("Game Over\nYour Score Is: " + std::to_string(score));
                    return;
                }
            }
        }
    }
}

void Game::handleCollisionsWithObstacles() {
    if (hero) {
        for (auto& obstacle : obstacles) {
            if (hero->getBounds().intersects(obstacle->getBounds())) {
                resolveCollision(hero, obstacle);
            }
        }
    }

    for (auto& obj : gameObjects) {
        if (auto villain = std::dynamic_pointer_cast<Villain>(obj)) {
            for (auto& obstacle : obstacles) {
                if (villain->getBounds().intersects(obstacle->getBounds())) {
                    resolveCollision(villain, obstacle);
                }
            }
        }
    }
}

void Game::resolveCollision(std::shared_ptr<GameObject> obj, std::shared_ptr<Obstacle> obstacle) {
    sf::FloatRect objBounds = obj->getBounds();
    sf::FloatRect obstacleBounds = obstacle->getBounds();

    // Determine the overlap area
    float overlapLeft = objBounds.left + objBounds.width - obstacleBounds.left;
    float overlapRight = obstacleBounds.left + obstacleBounds.width - objBounds.left;
    float overlapTop = objBounds.top + objBounds.height - obstacleBounds.top;
    float overlapBottom = obstacleBounds.top + obstacleBounds.height - objBounds.top;

    // Determine the smallest overlap
    if (overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom) {
        obj->setPosition(sf::Vector2f(obstacleBounds.left - objBounds.width, obj->getPosition().y));
    }
    else if (overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom) {
        obj->setPosition(sf::Vector2f(obstacleBounds.left + obstacleBounds.width, obj->getPosition().y));
    }
    else if (overlapTop < overlapLeft && overlapTop < overlapRight && overlapTop < overlapBottom) {
        obj->setPosition(sf::Vector2f(obj->getPosition().x, obstacleBounds.top - objBounds.height));
    }
    else if (overlapBottom < overlapLeft && overlapBottom < overlapRight && overlapBottom < overlapTop) {
        obj->setPosition(sf::Vector2f(obj->getPosition().x, obstacleBounds.top + obstacleBounds.height));
    }
}

void Game::spawnVillain() {
    int side = std::rand() % 4;
    sf::Vector2f startPos;
    switch (side) {
    case 0:  // Top
        startPos = sf::Vector2f(std::rand() % window.getSize().x, -50.f);
        break;
    case 1:  // Right
        startPos = sf::Vector2f(window.getSize().x + 50.f, std::rand() % window.getSize().y);
        break;
    case 2:  // Bottom
        startPos = sf::Vector2f(std::rand() % window.getSize().x, window.getSize().y + 50.f);
        break;
    case 3:  // Left
        startPos = sf::Vector2f(-50.f, std::rand() % window.getSize().y);
        break;
    }

    std::shared_ptr<Villain> newVillain = std::make_shared<Villain>("villain.png", startPos, hero);
    addGameObject(newVillain);
}

void Game::initializeObstacles() {
    obstacles.push_back(std::make_shared<Obstacle>(sf::Vector2f(200.f, 150.f), sf::Vector2f(100.f, 20.f), sf::Color::Green));
    obstacles.push_back(std::make_shared<Obstacle>(sf::Vector2f(400.f, 300.f), sf::Vector2f(100.f, 20.f), sf::Color::Blue));
    obstacles.push_back(std::make_shared<Obstacle>(sf::Vector2f(600.f, 450.f), sf::Vector2f(100.f, 20.f), sf::Color::Red));

    for (const auto& obstacle : obstacles) {
        addGameObject(obstacle);
    }
}

void Game::render() {
    window.clear();
    for (const auto& obj : gameObjects) {
        obj->draw(window);
    }
    window.draw(scoreText);

    if (gameOver) {
        window.draw(gameOverText);
    }

    window.display();
}
