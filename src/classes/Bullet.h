#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet
{
public:
    Bullet(sf::Vector2f position, float rotation);
    void update();
    void draw(sf::RenderWindow& window) const;
    const sf::RectangleShape& getBulletShape() const;
    bool isActive() const;
    void deactivate();

private:
    sf::RectangleShape bulletShape;
    sf::Vector2f velocity;
    float speed;
    bool active;
};

// Declare the rotateVector function
sf::Vector2f rotateVector(const sf::Vector2f& vector, float rotation);

#endif // BULLET_H



