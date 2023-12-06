#include "Player.h"
#include "Asteroid.h"
#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

Player::Player(sf::RenderWindow& window) :
	window(window),
    invulnerable(false),
    reviveDelay(3.0f),
    gameRestartRequested(false),
    lives(3),
	score(0)

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

    if (invulnerable)
    {
        if (reviveTimer.getElapsedTime().asSeconds() < reviveDelay)
        {
            // Player is still in revive delay
            float alpha = static_cast<float>(std::sin(reviveTimer.getElapsedTime().asSeconds() * 10.0f)) * 0.5f + 0.5f;
            playerShape.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha * 255)));
        }
        else
        {
            // Revive delay is over, make player fully visible and reset invulnerability
            playerShape.setFillColor(sf::Color::White);
            invulnerable = false;
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

bool Player::isCollidingWithAsteroid(const Asteroid& asteroid) const {
    // Use the smaller hitbox for asteroid collision
    return playerShape.getGlobalBounds().intersects(asteroid.getCollisionBounds());
}

bool Player::isCollidingWithBullet(const Bullet& bullet) const
{
	return playerShape.getGlobalBounds().intersects(bullet.getBulletShape().getGlobalBounds());
}

void Player::handleAsteroidCollision([[maybe_unused]] const Asteroid& asteroid)
{
    if(!invulnerable){
     lives--;
     reviveTimer.restart();
     invulnerable = true;

    // Check if the player is out of lives
    if (lives <= 0) {
        gameOver = true;
    }
    else {
        // If the player still has lives, teleport to a random location
        teleportToRandomLocation();
    }
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

sf::Vector2f Player::getPosition() const {
    return playerShape.getPosition();  // Assuming 'playerShape' is the SFML shape representing the player
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


bool Player::isGameRestartRequested() const
{
    return gameRestartRequested;
}

void Player::resetGame()
{
    gameRestartRequested = false;
    lives = 3;
    // Reset any other game-related variables as needed
}

void Player::requestGameRestart()
{
    gameRestartRequested = true;
}

int Player::getLives() const {
    return lives;
}

std::vector<Bullet>& Player::getBullets()
{
    return bullets;
}
int Player::getScore() const {
	return score;
}

void Player::incrementScore(int points)
{
    score += points;
}