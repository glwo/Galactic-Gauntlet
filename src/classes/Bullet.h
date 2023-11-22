// Bullet.h
#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet
{
public:
    Bullet(sf::Vector2f position, float rotation);
    void update();
    void draw(sf::RenderWindow& window) const; // Marked as const
    const sf::RectangleShape& getBulletShape() const; // Marked as const
    bool isActive() const; // Add this function
    void deactivate(); // Remove const here

private:
    sf::RectangleShape bulletShape;
    sf::Vector2f velocity;
    float speed;
    bool active; // Add this attribute
};

#endif // BULLET_H



