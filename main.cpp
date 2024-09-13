//#include <SFML/Graphics.hpp>
//#include <vector>
//#include <memory>
//#include <iostream>
//#include <ctime>
//#include <cmath>
//
//// AnimatedSprite class
//class AnimatedSprite : public sf::Sprite {
//private:
//    sf::Texture texture;
//    std::vector<sf::IntRect> frames;
//    float frameRate; // Frames per second
//    float timeSinceLastFrame;
//    int currentFrame;
//
//public:
//    AnimatedSprite(float fps, const std::string& textureFile)
//        : frameRate(fps), timeSinceLastFrame(0.f), currentFrame(0) {
//        if (!texture.loadFromFile(textureFile)) {
//            std::cerr << "Failed to load texture!" << std::endl;
//        }
//        setTexture(texture);
//        if (!frames.empty()) {
//            setTextureRect(frames[0]);
//        }
//    }
//
//    void addAnimationFrame(const sf::IntRect& frame) {
//        frames.push_back(frame);
//        if (frames.size() == 1) { // Set the initial frame if this is the first frame
//            setTextureRect(frames[0]);
//        }
//    }
//
//    void update(float deltaTime) {
//        if (frames.empty()) {
//            return; // No frames to animate
//        }
//
//        timeSinceLastFrame += deltaTime;
//        if (timeSinceLastFrame >= 1.f / frameRate) {
//            timeSinceLastFrame = 0.f;
//            currentFrame = (currentFrame + 1) % frames.size();
//            setTextureRect(frames[currentFrame]);
//        }
//    }
//
//    void setAnimationFrames(const std::vector<sf::IntRect>& animationFrames) {
//        frames = animationFrames;
//        if (!frames.empty()) {
//            setTextureRect(frames[0]);
//        }
//    }
//};
//
//// Base class for all game objects
//class GameObject {
//public:
//    virtual void update(float deltaTime) = 0;
//    virtual void draw(sf::RenderWindow& window) = 0;
//    virtual sf::FloatRect getBounds() const = 0;
//    virtual sf::Vector2f getPosition() const = 0;
//    virtual void setPosition(const sf::Vector2f& position) = 0;
//    virtual ~GameObject() = default;
//};
//
//// Hero class
//class Hero : public GameObject {
//private:
//    std::shared_ptr<AnimatedSprite> sprite;
//    float speed;
//
//public:
//    Hero(const std::string& textureFile) {
//        sprite = std::make_shared<AnimatedSprite>(10.0f, textureFile);
//
//        // Define animation frames
//        sprite->addAnimationFrame(sf::IntRect(0, 0, 50, 37));  // Hero standing frame 1
//        sprite->addAnimationFrame(sf::IntRect(50, 0, 50, 37)); // Hero standing frame 2
//        sprite->addAnimationFrame(sf::IntRect(100, 0, 50, 37)); // Hero standing frame 3
//        sprite->addAnimationFrame(sf::IntRect(150, 0, 50, 37)); // Hero running frame 1
//        sprite->addAnimationFrame(sf::IntRect(200, 0, 50, 37)); // Hero running frame 2
//        sprite->addAnimationFrame(sf::IntRect(250, 0, 50, 37)); // Hero running frame 3
//        sprite->addAnimationFrame(sf::IntRect(300, 0, 50, 37)); // Hero running frame 4
//        sprite->addAnimationFrame(sf::IntRect(350, 0, 50, 37)); // Hero running frame 5
//        sprite->addAnimationFrame(sf::IntRect(400, 0, 50, 37)); // Hero running frame 6
//
//        sprite->setPosition(400.f, 300.f);
//        speed = 200.f;
//    }
//
//    void update(float deltaTime) override {
//        sf::Vector2f movement(0.f, 0.f);
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//            movement.x -= speed * deltaTime;
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//            movement.x += speed * deltaTime;
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//            movement.y -= speed * deltaTime;
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//            movement.y += speed * deltaTime;
//
//        sprite->move(movement);
//
//        // Keep hero within window bounds
//        sf::Vector2u windowSize = { 800, 600 };
//        sf::Vector2f heroPos = sprite->getPosition();
//        if (heroPos.x < 0) heroPos.x = 0;
//        if (heroPos.y < 0) heroPos.y = 0;
//        if (heroPos.x + sprite->getGlobalBounds().width > windowSize.x) heroPos.x = windowSize.x - sprite->getGlobalBounds().width;
//        if (heroPos.y + sprite->getGlobalBounds().height > windowSize.y) heroPos.y = windowSize.y - sprite->getGlobalBounds().height;
//        sprite->setPosition(heroPos);
//
//        sprite->update(deltaTime); // Update the animation
//    }
//
//    void draw(sf::RenderWindow& window) override {
//        window.draw(*sprite);
//    }
//
//    sf::FloatRect getBounds() const override {
//        return sprite->getGlobalBounds();
//    }
//
//    sf::Vector2f getPosition() const override {
//        return sprite->getPosition();
//    }
//
//    void setPosition(const sf::Vector2f& position) override {
//        sprite->setPosition(position);
//    }
//};
//
//// Villain class
//class Villain : public GameObject {
//private:
//    sf::Sprite sprite;
//    sf::Texture texture;
//    float speed;
//    sf::Vector2f direction;
//    std::shared_ptr<Hero> hero;
//
//public:
//    Villain(const std::string& textureFile, const sf::Vector2f& startPos, std::shared_ptr<Hero> heroPtr)
//        : hero(heroPtr) {
//        if (!texture.loadFromFile(textureFile)) {
//            std::cerr << "Failed to load villain texture!" << std::endl;
//        }
//        sprite.setTexture(texture);
//        sprite.setScale(0.05f, 0.05f);  // Set the scale for villains
//        sprite.setPosition(startPos);
//        speed = 100.f;
//        updateDirection();
//    }
//
//    void update(float deltaTime) override {
//        if (hero) {
//            updateDirection();
//            sprite.move(direction * speed * deltaTime);
//        }
//    }
//
//    void draw(sf::RenderWindow& window) override {
//        window.draw(sprite);
//    }
//
//    sf::FloatRect getBounds() const override {
//        return sprite.getGlobalBounds();
//    }
//
//    sf::Vector2f getPosition() const override {
//        return sprite.getPosition();
//    }
//
//    void setPosition(const sf::Vector2f& position) override {
//        sprite.setPosition(position);
//    }
//
//private:
//    void updateDirection() {
//        if (hero) {
//            sf::Vector2f heroPos = hero->getPosition();
//            sf::Vector2f currentPos = sprite.getPosition();
//            direction = heroPos - currentPos;
//            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
//            if (length != 0) {
//                direction /= length;
//            }
//        }
//    }
//};
//
//// Sword class
//class Sword : public GameObject {
//private:
//    sf::Sprite sprite;
//    sf::Texture texture;
//    std::shared_ptr<Hero> hero;
//
//public:
//    Sword(const std::string& textureFile, std::shared_ptr<Hero> heroPtr) : hero(heroPtr) {
//        if (!texture.loadFromFile(textureFile)) {
//            std::cerr << "Failed to load sword texture!" << std::endl;
//        }
//        sprite.setTexture(texture);
//        sprite.setScale(0.05f, 0.05f);
//        updatePosition();
//    }
//
//    void update(float deltaTime) override {
//        updatePosition();
//    }
//
//    void draw(sf::RenderWindow& window) override {
//        window.draw(sprite);
//    }
//
//    sf::FloatRect getBounds() const override {
//        return sprite.getGlobalBounds();
//    }
//
//    sf::Vector2f getPosition() const override {
//        return sprite.getPosition();
//    }
//
//    void setPosition(const sf::Vector2f& position) override {
//        sprite.setPosition(position);
//    }
//
//private:
//    void updatePosition() {
//        if (hero) {
//            sf::Vector2f heroPos = hero->getPosition();
//            sprite.setPosition(heroPos.x + hero->getBounds().width, heroPos.y + hero->getBounds().height / 2.f - sprite.getGlobalBounds().height / 2.f);
//        }
//    }
//};
//
//// Obstacle class
//class Obstacle : public GameObject {
//private:
//    sf::RectangleShape rectangle;
//
//public:
//    Obstacle(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color) {
//        rectangle.setSize(size);
//        rectangle.setFillColor(color);
//        rectangle.setPosition(position);
//    }
//
//    void update(float deltaTime) override {
//        // Obstacles are static, so no update needed
//    }
//
//    void draw(sf::RenderWindow& window) override {
//        window.draw(rectangle);
//    }
//
//    sf::FloatRect getBounds() const override {
//        return rectangle.getGlobalBounds();
//    }
//
//    sf::Vector2f getPosition() const override {
//        return rectangle.getPosition();
//    }
//
//    void setPosition(const sf::Vector2f& position) override {
//        rectangle.setPosition(position);
//    }
//};
//
//// Game class
//class Game {
//private:
//    sf::RenderWindow window;
//    std::vector<std::shared_ptr<GameObject>> gameObjects;
//    std::shared_ptr<Hero> hero;
//    std::shared_ptr<Sword> sword;
//    int score;
//    sf::Font font;
//    sf::Text scoreText;
//    sf::Text gameOverText;
//    sf::Clock villainSpawnClock;
//    bool gameOver;
//
//    std::vector<std::shared_ptr<Obstacle>> obstacles;
//
//public:
//    Game() : window(sf::VideoMode(800, 600), "2D Game"), score(0), gameOver(false) {
//        if (!font.loadFromFile("BebasNeue-Regular.ttf")) {
//            std::cerr << "Failed to load font!" << std::endl;
//        }
//        scoreText.setFont(font);
//        scoreText.setCharacterSize(24);
//        scoreText.setFillColor(sf::Color::White);
//        scoreText.setPosition(10.f, 10.f);
//
//        gameOverText.setFont(font);
//        gameOverText.setCharacterSize(48);
//        gameOverText.setFillColor(sf::Color::Red);
//
//        sf::Vector2u windowSize = window.getSize();
//        gameOverText.setPosition(windowSize.x / 2.f - gameOverText.getGlobalBounds().width / 2.f, windowSize.y / 2.f - gameOverText.getGlobalBounds().height / 2.f);
//
//        std::srand(static_cast<unsigned>(std::time(nullptr)));
//
//        // Initialize obstacles
//        initializeObstacles();
//
//        // Initialize hero and sword
//        std::shared_ptr<Hero> heroObj = std::make_shared<Hero>("animation.png");
//        setHero(heroObj);
//
//        std::shared_ptr<Sword> swordObj = std::make_shared<Sword>("sword.png", heroObj);
//        setSword(swordObj);
//    }
//
//    void addGameObject(const std::shared_ptr<GameObject>& object) {
//        gameObjects.push_back(object);
//    }
//
//    void setHero(const std::shared_ptr<Hero>& heroObj) {
//        hero = heroObj;
//        addGameObject(hero);
//    }
//
//    void setSword(const std::shared_ptr<Sword>& swordObj) {
//        sword = swordObj;
//        addGameObject(sword);
//    }
//
//    void run() {
//        sf::Clock clock;
//        while (window.isOpen()) {
//            sf::Time deltaTime = clock.restart();
//            processEvents();
//            if (!gameOver) {
//                update(deltaTime.asSeconds());
//            }
//            render();
//        }
//    }
//
//    void processEvents() {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//    }
//
//    void update(float deltaTime) {
//        if (!gameOver) {
//            for (auto& obj : gameObjects) {
//                obj->update(deltaTime);
//            }
//
//            // Spawn villains periodically
//            if (villainSpawnClock.getElapsedTime().asSeconds() > 4.f) {
//                spawnVillain();
//                villainSpawnClock.restart();
//            }
//
//            checkCollisions();
//            handleCollisionsWithObstacles();
//
//            scoreText.setString("Score: " + std::to_string(score));
//        }
//    }
//
//    void checkCollisions() {
//        if (hero && sword) {
//            for (auto it = gameObjects.begin(); it != gameObjects.end(); ) {
//                if (auto villain = std::dynamic_pointer_cast<Villain>(*it)) {
//                    if (sword->getBounds().intersects(villain->getBounds())) {
//                        // Remove the villain and increase the score
//                        it = gameObjects.erase(it);
//                        score++;
//                    }
//                    else {
//                        ++it;
//                    }
//                }
//                else {
//                    ++it;
//                }
//            }
//
//            // Check if hero collides with any villains
//            for (const auto& obj : gameObjects) {
//                if (auto villain = std::dynamic_pointer_cast<Villain>(obj)) {
//                    if (villain->getBounds().intersects(hero->getBounds())) {
//                        gameOver = true;
//                        gameOverText.setString("Game Over\nYour Score Is: " + std::to_string(score));
//                        return;
//                    }
//                }
//            }
//        }
//    }
//
//    void handleCollisionsWithObstacles() {
//        if (hero) {
//            for (auto& obstacle : obstacles) {
//                if (hero->getBounds().intersects(obstacle->getBounds())) {
//                    resolveCollision(hero, obstacle);
//                }
//            }
//        }
//
//        for (auto& obj : gameObjects) {
//            if (auto villain = std::dynamic_pointer_cast<Villain>(obj)) {
//                for (auto& obstacle : obstacles) {
//                    if (villain->getBounds().intersects(obstacle->getBounds())) {
//                        resolveCollision(villain, obstacle);
//                    }
//                }
//            }
//        }
//    }
//
//    void resolveCollision(std::shared_ptr<GameObject> obj, std::shared_ptr<Obstacle> obstacle) {
//        sf::FloatRect objBounds = obj->getBounds();
//        sf::FloatRect obstacleBounds = obstacle->getBounds();
//
//        // Determine the overlap area
//        float overlapLeft = objBounds.left + objBounds.width - obstacleBounds.left;
//        float overlapRight = obstacleBounds.left + obstacleBounds.width - objBounds.left;
//        float overlapTop = objBounds.top + objBounds.height - obstacleBounds.top;
//        float overlapBottom = obstacleBounds.top + obstacleBounds.height - objBounds.top;
//
//        // Determine the smallest overlap
//        if (overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom) {
//            obj->setPosition(sf::Vector2f(obstacleBounds.left - objBounds.width, obj->getPosition().y));
//        }
//        else if (overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom) {
//            obj->setPosition(sf::Vector2f(obstacleBounds.left + obstacleBounds.width, obj->getPosition().y));
//        }
//        else if (overlapTop < overlapLeft && overlapTop < overlapRight && overlapTop < overlapBottom) {
//            obj->setPosition(sf::Vector2f(obj->getPosition().x, obstacleBounds.top - objBounds.height));
//        }
//        else if (overlapBottom < overlapLeft && overlapBottom < overlapRight && overlapBottom < overlapTop) {
//            obj->setPosition(sf::Vector2f(obj->getPosition().x, obstacleBounds.top + obstacleBounds.height));
//        }
//    }
//
//    void spawnVillain() {
//        int side = std::rand() % 4;
//        sf::Vector2f startPos;
//        switch (side) {
//        case 0:  // Top
//            startPos = sf::Vector2f(std::rand() % window.getSize().x, -50.f);
//            break;
//        case 1:  // Right
//            startPos = sf::Vector2f(window.getSize().x + 50.f, std::rand() % window.getSize().y);
//            break;
//        case 2:  // Bottom
//            startPos = sf::Vector2f(std::rand() % window.getSize().x, window.getSize().y + 50.f);
//            break;
//        case 3:  // Left
//            startPos = sf::Vector2f(-50.f, std::rand() % window.getSize().y);
//            break;
//        }
//
//        std::shared_ptr<Villain> newVillain = std::make_shared<Villain>("villain.png", startPos, hero);
//        addGameObject(newVillain);
//    }
//
//    void initializeObstacles() {
//        obstacles.push_back(std::make_shared<Obstacle>(sf::Vector2f(200.f, 150.f), sf::Vector2f(100.f, 20.f), sf::Color::Green));
//        obstacles.push_back(std::make_shared<Obstacle>(sf::Vector2f(400.f, 300.f), sf::Vector2f(100.f, 20.f), sf::Color::Blue));
//        obstacles.push_back(std::make_shared<Obstacle>(sf::Vector2f(600.f, 450.f), sf::Vector2f(100.f, 20.f), sf::Color::Red));
//
//        for (const auto& obstacle : obstacles) {
//            addGameObject(obstacle);
//        }
//    }
//
//    void render() {
//        window.clear();
//        for (const auto& obj : gameObjects) {
//            obj->draw(window);
//        }
//        window.draw(scoreText);
//
//        if (gameOver) {
//            window.draw(gameOverText);
//        }
//
//        window.display();
//    }
//};
//
//int main() {
//    Game game;
//    game.run();
//    return 0;
//}
#include "Game.hpp"

int main() {
    Game game;
    game.run();
    return 0;
}
