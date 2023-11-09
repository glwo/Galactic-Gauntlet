#include "Asteroid.h"

Asteroid::Asteroid(sf::Vector2f position, float rotation)
{
    asteroidShape = sf::ConvexShape(4);
    // Initialize the asteroid shape based on size
    // You can define the points and size here based on your needs
    asteroidShape.setFillColor(sf::Color::Red);
    asteroidShape.setPosition(position);
    asteroidShape.setRotation(rotation);
    // Initialize other properties
}

void Asteroid::update()
{
    // Update the asteroid's position, rotation, etc.
}

void Asteroid::draw(sf::RenderWindow& window) const
{
    window.draw(asteroidShape);
}

bool Asteroid::isCollidingWith(const sf::FloatRect& otherBounds) const
{
    // Check for collisions with otherBounds
    // You may need to implement collision detection logic
    // and return true if a collision occurs, otherwise false
    return asteroidShape.getGlobalBounds().intersects(otherBounds);
}

const sf::ConvexShape& Asteroid::getAsteroidShape() const
{
    return asteroidShape;
}
