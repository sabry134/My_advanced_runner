#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <algorithm>

const int SHAPE_SPACING = 150;
const float FRAME_WIDTH = 37.3f;
const int FRAME_HEIGHT = 50;
const int NUM_FRAMES = 11; // The number of frames in the animation
const float ANIMATION_FRAME_TIME = 0.1f; // Time in seconds for each animation frame

void open_window(std::vector<int>& clientSockets) {
    sf::RenderWindow window(sf::VideoMode(800, 500), "My advanced runner");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("img/runner_background.jpg")) {
        std::cerr << "Error loading background texture." << std::endl;
        exit(1);
    }

    sf::Texture persoTexture;
    if (!persoTexture.loadFromFile("img/running_mario.png")) {
        std::cerr << "Error loading perso texture." << std::endl;
        exit(1);
    }

    // Create a sprite to hold the background texture
    sf::Sprite backgroundSprite(backgroundTexture);

    // Create a vector to hold the client sprites
    std::vector<sf::Sprite> clientSprites;

    int currentFrame = 0; // The current frame index in the animation
    sf::Clock animationClock; // Clock for controlling animation frames

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                std::cout << "Server has been closed!" << std::endl;
                exit(84);
            } else if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                window.setView(sf::View(visibleArea));
            }
        }

        // Update animation frames at a fixed frame rate
        if (animationClock.getElapsedTime().asSeconds() >= ANIMATION_FRAME_TIME) {
            currentFrame = (currentFrame + 1) % NUM_FRAMES;
            animationClock.restart();
        }

        window.clear();

        // Draw the background
        window.draw(backgroundSprite);

        // Update the number of client sprites based on the number of clients
        while (clientSprites.size() < clientSockets.size()) {
            sf::Sprite clientSprite(persoTexture);
            clientSprites.push_back(clientSprite);
        }

        // Find the disconnected clients' sprites and remove them
        for (auto it = clientSprites.begin(); it != clientSprites.end();) {
            if (static_cast<std::size_t>(std::distance(clientSprites.begin(), it)) >= clientSockets.size()) {
                it = clientSprites.erase(it);
            } else {
                ++it;
            }
        }

        // Set the positions and draw the client sprites
        for (std::size_t i = 0; i < clientSprites.size(); ++i) {
            // Custom X and Y positions (you can modify these values)
            float x = 100.0f + i * SHAPE_SPACING;
            float y = 900.0f;

            clientSprites[i].setPosition(x, y);
            clientSprites[i].setTextureRect(sf::IntRect(currentFrame * FRAME_WIDTH, 0, FRAME_WIDTH, FRAME_HEIGHT));
            window.draw(clientSprites[i]);
        }

        window.display();
    }
}
