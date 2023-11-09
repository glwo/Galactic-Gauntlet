#include "classes/Asteroid.h"
#include "classes/Player.h"
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(1200, 800), "Asteroids", sf::Style::Default);
	window.setFramerateLimit(60);
	window.clear(sf::Color::Black);

	Player player(window); // Create the player object
	std::vector<Asteroid> asteroids;

	sf::Clock asteroidSpawnTimer;
	float asteroidSpawnInterval = 2.0f; // Adjust the interval as needed

	// Example: Add some initial asteroids
	asteroids.push_back(Asteroid::createRandomAsteroid(window));
	asteroids.push_back(Asteroid::createRandomAsteroid(window));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		player.update();

		// Check if enough time has passed to spawn a new asteroid
		if (asteroidSpawnTimer.getElapsedTime().asSeconds() >= asteroidSpawnInterval)
		{
			asteroids.push_back(Asteroid::createRandomAsteroid(window));

			// Restart the timer for the next asteroid spawn
			asteroidSpawnTimer.restart();
		}

		// Update and handle collisions for asteroids
		// Update and handle collisions for asteroids
		for (auto& asteroid : asteroids)
		{
			asteroid.update(window); // Pass the window object
			// Check for collisions with the player
			if (player.isCollidingWithAsteroid(asteroid))
			{
				player.handleAsteroidCollision(asteroid);
			}
		}

		// Check if enough time has passed to spawn a new asteroid
		if (asteroidSpawnTimer.getElapsedTime().asSeconds() >= asteroidSpawnInterval)
		{
			asteroids.push_back(Asteroid::createRandomAsteroid(window));

			// Restart the timer for the next asteroid spawn
			asteroidSpawnTimer.restart();
		}

		window.clear();
		player.draw(window);

		// Draw asteroids
		for (const auto& asteroid : asteroids)
		{
			asteroid.draw(window);
		}

		window.display();
	}

	return EXIT_SUCCESS;
}
