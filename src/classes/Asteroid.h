// Asteroid.h
#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>

class Asteroid
{
public:
    Asteroid(sf::Vector2f position, float rotation, float size);
    void update(sf::RenderWindow& window); // Pass the window as a parameter
    void draw(sf::RenderWindow& window) const;
    const sf::ConvexShape& getAsteroidShape() const;
    bool isCollidingWith(const sf::FloatRect& otherBounds) const;
    static Asteroid createRandomAsteroid(sf::RenderWindow& window);
    void setVelocity(const sf::Vector2f& newVelocity);

private:
    sf::ConvexShape asteroidShape;
    sf::Vector2f velocity;
    float speed;
};

#endif // ASTEROID_H


