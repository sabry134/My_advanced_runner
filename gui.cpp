#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

const int SHAPE_SPACING = 150;

void open_window(std::vector<int>& clientSockets) {
    sf::RenderWindow window(sf::VideoMode(800, 500), "SFML Shapes Window");

    // Load the background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("img/runner_background.jpg")) {
        std::cerr << "Error loading background texture." << std::endl;
        exit(1);
    }

    // Create a sprite to hold the background texture
    sf::Sprite backgroundSprite(backgroundTexture);

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

        window.clear();

        // Draw the background
        window.draw(backgroundSprite);

        int numShapes = clientSockets.size();

        for (int i = 0; i < numShapes; i++) {
            float x = 100.0f + i * SHAPE_SPACING;
            float y = 300.0f;
            sf::CircleShape circle(50);
            circle.setFillColor(sf::Color::Red);
            circle.setPosition(x, y);
            window.draw(circle);
        }

        window.display();
    }
}

