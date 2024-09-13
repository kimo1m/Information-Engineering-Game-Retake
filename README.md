Welcome to the 2D Game project! This README provides information on how to set up, run, and understand the game.

Overview
This is a 2D game developed using C++ and SFML (Simple and Fast Multimedia Library). The game features a hero character that can move around the screen and interact with villains, obstacles, and a sword. The goal is to avoid villains, use the sword to defeat them, and achieve a high score.

Features
Hero Character: Moveable sprite with animations.
Villains: Enemies that move towards the hero.
Sword: Weapon that can be used to defeat villains.
Obstacles: Static objects that the hero and villains must navigate around.
Score System: Track and display the player’s score.
Game Over State: Display game over text when the hero collides with a villain.

Prerequisites
To build and run this game, you need:
1- C++ Compiler: Ensure you have a C++ compiler (GCC, Clang, MSVC, etc.).
2- SFML: Download and install SFML from SFML's official website.

Setup

Clone the Repository
bash
Copy code
git clone [https://github.com/kimo1m/Information-Engineering-Game-Retake.git]
cd yourrepository
Install SFML

Follow the installation instructions for SFML from their website and ensure SFML is correctly set up in your development environment.

Build the Project Using CMake:
bash
Copy code
mkdir build
cd build
cmake ..
make

Manual Compilation (if not using CMake):
bash
Copy code
g++ -o game main.cpp AnimatedSprite.cpp Hero.cpp Villain.cpp Sword.cpp Obstacle.cpp Game.cpp -lsfml-graphics -lsfml-window -lsfml-system

After building, run the executable:
bash
Copy code
./game

Controls
Arrow Keys: Move the hero (Up, Down, Left, Right).
Space Bar: Use the sword (if applicable, depends on implementation).

Assets
Textures: Place the texture files (e.g., animation.png, sword.png, villain.png) in the project’s root directory or adjust the file paths in the code accordingly.
Fonts: Ensure BebasNeue-Regular.ttf is available in the root directory or update the path in the code.

Game Mechanics
Hero: The player controls the hero character. The hero can move around the screen and use a sword to defeat villains.
Villains: Villains spawn at random intervals and move towards the hero. They must be defeated by the sword to avoid game over.
Obstacles: Static objects that both the hero and villains need to navigate around. Collisions with obstacles are resolved to prevent passing through them.

Troubleshooting
Linker Errors: Ensure SFML libraries are correctly linked in your project. Verify that the SFML version matches the one used in the code.
Missing Assets: Check that all required textures and fonts are present in the correct locations.

Contributing
Feel free to contribute to the project by submitting issues or pull requests. For major changes, please open an issue first to discuss what you would like to change.

Contact
If you have any questions or need further assistance, you can reach out to [Kareem Mohamed] at [kareem.mohamed@student.put.poznan.pl].

Feel free to adjust any sections as needed, such as updating file paths, build instructions, or contact information.
