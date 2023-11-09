// Asteroid.cpp
#include "Asteroid.h"
#include <random>

Asteroid::Asteroid(sf::Vector2f position, float rotation, float size)
{
    asteroidShape = sf::ConvexShape(8);
    asteroidShape.setFillColor(sf::Color::Red);
    asteroidShape.setPosition(position);
    asteroidShape.setRotation(rotation);

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
    speed = speedDist(gen);
    std::uniform_real_distribution<float> angleDist(0.0f, 360.0f);
    float angle = angleDist(gen);
    velocity = sf::Vector2f(std::cos(angle * 3.14159265f / 180.0f), std::sin(angle * 3.14159265f / 180.0f)) * speed;
}

Asteroid Asteroid::createRandomAsteroid(sf::RenderWindow& window)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xDist(0.0f, static_cast<float>(window.getSize().x));
    std::uniform_real_distribution<float> yDist(0.0f, static_cast<float>(window.getSize().y));
    std::uniform_real_distribution<float> rotationDist(0.0f, 360.0f);
    std::uniform_real_distribution<float> speedDist(1.0f, 5.0f);

    sf::Vector2f position(xDist(gen), yDist(gen));
    float rotation = rotationDist(gen);
    float speed = speedDist(gen);

    Asteroid asteroid(position, rotation, 3.0f);

    // Give the asteroid a random velocity in a random direction
    float angle = rotationDist(gen);
    asteroid.setVelocity(sf::Vector2f(std::cos(angle * 3.14159265f / 180.0f), std::sin(angle * 3.14159265f / 180.0f)) * speed);

    return asteroid;
}

void Asteroid::update(sf::RenderWindow& window)
{
    // Check if the asteroid has a texture (e.g., before calling asteroidShape.getTexture())
    if (asteroidShape.getTexture())
    {
        // Update the asteroid's position based on its velocity
        asteroidShape.move(velocity);

        // Check if the asteroid is outside the screen bounds
        sf::Vector2f position = asteroidShape.getPosition();
        sf::Vector2u windowSize = window.getSize(); // Use the window parameter
        float halfWidth = asteroidShape.getGlobalBounds().width / 2.0f;
        float halfHeight = asteroidShape.getGlobalBounds().height / 2.0f;

        if (position.x + halfWidth < 0.0f)
            position.x = windowSize.x + halfWidth;
        else if (position.x - halfWidth > windowSize.x)
            position.x = -halfWidth;

        if (position.y + halfHeight < 0.0f)
            position.y = windowSize.y + halfHeight;
        else if (position.y - halfHeight > windowSize.y)
            position.y = -halfHeight;

        asteroidShape.setPosition(position);
    }
}

void Asteroid::setVelocity(const sf::Vector2f& newVelocity)
{
    velocity = newVelocity * speed; // Multiply by speed to maintain the magnitude
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