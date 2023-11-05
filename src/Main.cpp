#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Player {
public:
    Player() {
        // Initialize player's position, speed, and other attributes
        // You can add more properties as needed
        playerShape = sf::ConvexShape(3); // Create a triangle shape
        playerShape.setPoint(0, sf::Vector2f(0, -20));
        playerShape.setPoint(1, sf::Vector2f(-20, 20));
        playerShape.setPoint(2, sf::Vector2f(20, 20));
        playerShape.setFillColor(sf::Color::White);
        playerShape.setPosition(400, 300); // Set the initial position
    }

    void update([[maybe_unused]] sf::RenderWindow& window) {
        // Implement player's movement and shooting logic here
        // You can use keyboard or mouse input for control

        // For example, move the player left when the A key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            playerShape.move(-5.0f, 0);
        }
        // Add similar logic for other controls
    }

    void draw([[maybe_unused]] sf::RenderWindow& window) {
        // Render the player's shape on the window
        window.draw(playerShape);
    }

private:
    sf::ConvexShape playerShape; // Shape representing the player
};

int main() {
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600), "Asteroids", sf::Style::Default);
    window.setFramerateLimit(60);
    window.clear(sf::Color::Black); // Set the background color to black

    Player player; // Create the player object

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Handle player controls
        player.update(window);

        window.clear(); // Clear the window (clears to the background color)

        // Draw game objects, including the player's shape
        player.draw(window);

        window.display();
    }

    return EXIT_SUCCESS;
}


