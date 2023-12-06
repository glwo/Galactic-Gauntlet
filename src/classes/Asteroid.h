// Asteroid.h
#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


class Player;  // Forward declaration

class Asteroid
{
public:
    Asteroid(sf::Vector2f position, float rotation, float size, Player& player);
    void update(sf::RenderWindow& window); // Pass the window as a parameter
    void draw(sf::RenderWindow& window) const;
    const sf::ConvexShape& getAsteroidShape() const;
    bool isCollidingWith(const sf::FloatRect& otherBounds) const;
    static Asteroid createRandomAsteroid(sf::RenderWindow& window, Player& player);
    void setVelocity(const sf::Vector2f& newVelocity);
    static constexpr float AsteroidHitboxMultiplier = 0.5f;
    sf::FloatRect getCollisionBounds() const;
    bool isDestroyed() const;
    void destroy();

private:
    sf::ConvexShape asteroidShape;
    sf::Vector2f velocity;
    float speed;
    bool destroyed; 
    void moveAsteroid();
    sf::Sprite explosionSprite;
    sf::Texture explosionTexture;
    bool isExploding;
    sf::CircleShape explosionShape;
    Player& player; 
};

#endif // ASTEROID_H


