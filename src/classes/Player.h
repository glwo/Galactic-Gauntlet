#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Bullet.h"

class Player
{
public:
    Player(sf::RenderWindow& window);
    void update();
    void draw(sf::RenderWindow& window);

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
    
    void teleportToRandomLocation();
};

#endif // PLAYER_H
