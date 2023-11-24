// Asteroid.cpp
#include "Asteroid.h"
#include "Player.h"
#include <random>
#include <iostream>
#include <SFML/System.hpp>

Asteroid::Asteroid(sf::Vector2f position, float rotation, float size)
	:destroyed(false)
{
	asteroidShape = sf::ConvexShape(8);
	asteroidShape.setFillColor(sf::Color::Red);
	asteroidShape.setPosition(position);
	asteroidShape.setRotation(rotation);

	// Utilize the 'size' parameter to scale the asteroid's shape
	asteroidShape.setPoint(0, sf::Vector2f(0, -20 * size));
	asteroidShape.setPoint(1, sf::Vector2f(10 * size, -10 * size));
	asteroidShape.setPoint(2, sf::Vector2f(20 * size, -15 * size));
	asteroidShape.setPoint(3, sf::Vector2f(25 * size, 0));
	asteroidShape.setPoint(4, sf::Vector2f(20 * size, 15 * size));
	asteroidShape.setPoint(5, sf::Vector2f(10 * size, 10 * size));
	asteroidShape.setPoint(6, sf::Vector2f(5 * size, 20 * size));
	asteroidShape.setPoint(7, sf::Vector2f(0, 15 * size));

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> speedDist(2.0f, 5.0f);
	float speed = speedDist(gen);
	std::uniform_real_distribution<float> angleDist(0.0f, 360.0f);
	float angle = angleDist(gen);
	sf::Vector2f velocity = sf::Vector2f(std::cos(angle * 3.14159265f / 180.0f), std::sin(angle * 3.14159265f / 180.0f)) * speed;

	setVelocity(velocity);
    // setVelocity({1, 1});
}

Asteroid Asteroid::createRandomAsteroid(sf::RenderWindow& window, const Player& player)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> xDist(0.0f, static_cast<float>(window.getSize().x));
	std::uniform_real_distribution<float> yDist(0.0f, static_cast<float>(window.getSize().y));
	std::uniform_real_distribution<float> rotationDist(0.0f, 360.0f);
	std::uniform_real_distribution<float> speedDist(1.0f, 5.0f);

	const float minDistance = 200.0f; // Adjust this value as needed

	sf::Vector2f position;
	float distance;
	do
	{
		position = sf::Vector2f(xDist(gen), yDist(gen));
		distance = std::hypotf(position.x - player.getPosition().x, position.y - player.getPosition().y);
	} while (distance < minDistance);

	float rotation = rotationDist(gen);
	float speed = speedDist(gen);

	// std::cout << "Generated Position: (" << position.x << ", " << position.y << ")" << std::endl;
	// std::cout << "Generated Rotation: " << rotation << std::endl;
	// std::cout << "Generated Speed: " << speed << std::endl;

	Asteroid asteroid(position, rotation, 3.0f);

	float angle = rotationDist(gen);
	asteroid.setVelocity(sf::Vector2f(std::cos(angle * 3.14159265f / 180.0f), std::sin(angle * 3.14159265f / 180.0f)) * speed);

	// asteroid.setVelocity(sf::Vector2f({1, 1}));

	return asteroid;
}

void Asteroid::update(sf::RenderWindow& window)
{
	// Update the asteroid's position based on its velocity

	if (!destroyed)
	{
		//  std::cout << "Asteroid Update - Before Move" << std::endl;
        // std::cout << "Velocity: " << velocity.x << " " << velocity.y << std::endl;
        // asteroidShape.move(velocity);
		moveAsteroid();

		// std::cout << "Asteroid Update - After Move" << std::endl;

		sf::Vector2f position = asteroidShape.getPosition();
		sf::Vector2u windowSize = window.getSize();
		sf::FloatRect asteroidBounds = asteroidShape.getGlobalBounds();

		if (position.x + asteroidBounds.width / 2 < 0.0f)
			asteroidShape.setPosition(windowSize.x + asteroidBounds.width / 2, position.y);
		else if (position.x - asteroidBounds.width / 2 > windowSize.x)
			asteroidShape.setPosition(-asteroidBounds.width / 2, position.y);

		if (position.y + asteroidBounds.height / 2 < 0.0f)
			asteroidShape.setPosition(position.x, windowSize.y + asteroidBounds.height / 2);
		else if (position.y - asteroidBounds.height / 2 > windowSize.y)
			asteroidShape.setPosition(position.x, -asteroidBounds.height / 2);
	}
}

void Asteroid::setVelocity(const sf::Vector2f& newVelocity)
{
	velocity = newVelocity;
}

void Asteroid::draw(sf::RenderWindow& window) const
{
	window.draw(asteroidShape);
}

bool Asteroid::isCollidingWith(const sf::FloatRect& otherBounds) const
{
	return asteroidShape.getGlobalBounds().intersects(otherBounds);
}

const sf::ConvexShape& Asteroid::getAsteroidShape() const
{
	return asteroidShape;
}

sf::FloatRect Asteroid::getCollisionBounds() const
{
	// Retrieve the bounds of the asteroid's shape
	sf::FloatRect bounds = asteroidShape.getGlobalBounds();

	// Reduce the bounds by a fixed factor (e.g., 30% smaller)
	sf::FloatRect smallerBounds(
		bounds.left + bounds.width * 0.14f,
		bounds.top + bounds.height * 0.14f,
		bounds.width * 0.6f,
		bounds.height * 0.6f);

	return smallerBounds;
}

bool Asteroid::isDestroyed() const
{
    return destroyed;
}

void Asteroid::destroy()
{
    destroyed = true;
    // Additional logic for explosion animation or any other effects
}

void Asteroid::moveAsteroid() {
  asteroidShape.move(velocity);
}