#include "Player.h"
#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

Player::Player(sf::RenderWindow& window) : window(window)
{
        playerShape = sf::ConvexShape(3);			   // Create a triangle shape
		playerShape.setPoint(0, sf::Vector2f(0, -20)); // Set the top as the front of the ship
		playerShape.setPoint(1, sf::Vector2f(-10, 10));
		playerShape.setPoint(2, sf::Vector2f(10, 10));
		playerShape.setFillColor(sf::Color::White);
		playerShape.setOrigin(0, -5);	   // Set the origin at the front of the ship
		playerShape.setPosition(400, 300); // Set the initial position
		velocity = sf::Vector2f(0, 0);	   // Initial velocity
		acceleration = 0.2f;			   // Adjust this value for desired acceleration
		maxSpeed = 5.0f;				   // Adjust this value for desired max speed
		rotationSpeed = 3.0f;			   // Adjust this value for desired rotation speed
		teleportCooldown.restart();
		shootingTimer.restart();
		shootDelay = 0.25f; // 0.25 seconds delay between shots
}

void Player::update()
{
    bool isLeftKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        bool isRightKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        bool isUpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        bool isSpaceKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

        // Apply rotation based on arrow key input
        if (isLeftKeyPressed)
        {
            playerShape.rotate(-rotationSpeed);
        }
        if (isRightKeyPressed)
        {
            playerShape.rotate(rotationSpeed);
        }

        // Calculate the direction vector for the ship's current rotation
        float radians = playerShape.getRotation() * 3.14159265f / 180.0f;
        sf::Vector2f direction(std::sin(radians), -std::cos(radians));

        // Apply acceleration in the forward direction
        if (isUpKeyPressed)
        {
            velocity += direction * acceleration;
        }

        // Shooting logic
        if (isSpaceKeyPressed)
        {
            // Check if enough time has passed since the last shot
            if (shootingTimer.getElapsedTime().asSeconds() >= shootDelay)
            {
                bullets.push_back(Bullet(playerShape.getPosition(), playerShape.getRotation()));
                shootingTimer.restart();
            }
        }

        // Apply damping to simulate space friction (optional)
        // velocity *= damping

        float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        if (speed > maxSpeed)
        {
            velocity *= maxSpeed / speed;
        }

        // Update position based on velocity
        playerShape.move(velocity);

        // Implement screen wrapping
        sf::Vector2f position = playerShape.getPosition();
        if (position.x < 0)
        {
            playerShape.setPosition(window.getSize().x, position.y);
        }
        else if (position.x > window.getSize().x)
        {
            playerShape.setPosition(0, position.y);
        }
        if (position.y < 0)
        {
            playerShape.setPosition(position.x, window.getSize().y);
        }
        else if (position.y > window.getSize().y)
        {
            playerShape.setPosition(position.x, 0);
        }

        // Update bullets
        for (auto& bullet : bullets)
        {
            bullet.update();
        }
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(playerShape);
    
    for (const auto& bullet : bullets)
    {
        bullet.draw(window);
    }
}

void Player::teleportToRandomLocation()
{
    // Check if the cooldown time has passed (5 seconds)
		if (teleportCooldown.getElapsedTime().asSeconds() >= 5.0f)
		{
			// Generate random coordinates within the window's bounds
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float> xDist(0.0f, static_cast<float>(window.getSize().x));
			std::uniform_real_distribution<float> yDist(0.0f, static_cast<float>(window.getSize().y));

			// Set the player's position to the random coordinates
			playerShape.setPosition(xDist(gen), yDist(gen));

			// Restart the cooldown timer
			teleportCooldown.restart();
		}
		else
		{
			return;
		}
}
