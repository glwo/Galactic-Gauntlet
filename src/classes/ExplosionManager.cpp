// ExplosionManager.cpp
#include "ExplosionManager.h"

ExplosionManager::ExplosionManager()
{
    if (!explosionTexture.loadFromFile("src/textures/explosion00.png"))
	{
		// std::cout << "Texture not loaded" << std::endl;
	}
}

void ExplosionManager::addExplosion(sf::Vector2f position)
{
    sf::Sprite explosionSprite;
    explosionSprite.setTexture(explosionTexture);
    explosionSprite.setOrigin(explosionTexture.getSize().x / 2.0f, explosionTexture.getSize().y / 2.0f);
    explosionSprite.setPosition(position);

    explosions.push_back(explosionSprite);
}

void ExplosionManager::update()
{
    // Update explosion animations, e.g., scale down the sprites
    for (auto& explosion : explosions)
    {
        explosion.setScale(explosion.getScale() * 0.98f);
    }

    // Remove finished explosions (scale < 0.1)
    explosions.erase(std::remove_if(explosions.begin(), explosions.end(),
                                     [](const sf::Sprite& explosion) { return explosion.getScale().x < 0.1f; }),
                     explosions.end());
}

void ExplosionManager::draw(sf::RenderWindow& window)
{
    // Draw all explosions
    for (const auto& explosion : explosions)
    {
        window.draw(explosion);
    }
}
