#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet
{
public:
    Bullet(sf::Vector2f position, float rotation);
    void update();
    void draw(sf::RenderWindow& window) const;
    const sf::RectangleShape& getBulletShape() const; // Function to get the bullet's shape

private:
    sf::RectangleShape bulletShape;
    sf::Vector2f velocity;
    float speed;
};

#endif // BULLET_H

