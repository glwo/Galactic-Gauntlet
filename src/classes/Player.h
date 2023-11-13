#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Bullet.h"


class Asteroid;

class Player {
public:
    Player(sf::RenderWindow& window);
    void update();
    void draw(sf::RenderWindow& window);
     bool isCollidingWithAsteroid(const Asteroid& asteroid) const; 
    void handleAsteroidCollision(const Asteroid& asteroid);
    bool isCollidingWithBullet(const Bullet& bullet) const;

    // Additional attributes for handling game states and player health
    void reduceHealth(int amount);
    int getHealth() const;
    bool isGameOver() const;

    // New method to retrieve player position
    sf::Vector2f getPosition() const;

private:
    sf::ConvexShape playerShape;
    sf::Vector2f velocity;
    float acceleration;
    float maxSpeed;
    float rotationSpeed;
    sf::Clock teleportCooldown;
    std::vector<Bullet> bullets;
    sf::Clock shootingTimer;
    float shootDelay;
    sf::RenderWindow& window;

    // Additional attributes for game state and health
    int health;
    bool gameOver;

    void teleportToRandomLocation();
};

#endif // PLAYER_H

