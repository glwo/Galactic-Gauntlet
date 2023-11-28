// ExplosionManager.h
#ifndef EXPLOSION_MANAGER_H
#define EXPLOSION_MANAGER_H

#include <SFML/Graphics.hpp>

class ExplosionManager
{
public:
    ExplosionManager();
    void addExplosion(sf::Vector2f position);
    void update();
    void draw(sf::RenderWindow& window);

private:
    std::vector<sf::Sprite> explosions;
    sf::Texture explosionTexture;
};

#endif // EXPLOSION_MANAGER_H
