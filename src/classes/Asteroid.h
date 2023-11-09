#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>

class Asteroid
{
public:
    Asteroid(sf::Vector2f position, float rotation);
    void update();
    void draw(sf::RenderWindow& window) const;
    const sf::ConvexShape& getAsteroidShape() const;
    bool isCollidingWith(const sf::FloatRect& otherBounds) const;

private:
    sf::ConvexShape asteroidShape; // Change this to sf::ConvexShape
    sf::Vector2f velocity;
    float speed;
};

#endif // ASTEROID_H



