#include "classes/Asteroid.h"
#include "classes/Player.h"
#include <SFML/Audio.hpp> // Include the audio library
#include <SFML/Graphics.hpp>
bool isGameOver = false;

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(1200, 800), "Asteroids", sf::Style::Default);
	window.setFramerateLimit(60);

	Player player(window); // Create the player object
	std::vector<Asteroid> asteroids;

	sf::Clock asteroidSpawnTimer;
	float asteroidSpawnInterval = 2.0f; // Adjust the interval as needed

	// Example: Add some initial asteroids
	asteroids.push_back(Asteroid::createRandomAsteroid(window, player));
	asteroids.push_back(Asteroid::createRandomAsteroid(window, player));

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

		if (!isGameOver)
		{
			if (asteroidSpawnTimer.getElapsedTime().asSeconds() >= asteroidSpawnInterval)
			{
				asteroids.push_back(Asteroid::createRandomAsteroid(window, player));
				asteroidSpawnTimer.restart();
			}

			for (auto& asteroid : asteroids)
			{
				asteroid.update(window);
				if (player.isCollidingWithAsteroid(asteroid))
				{
					player.handleAsteroidCollision(asteroid);
					isGameOver = true;
				}
			}
		}

		window.clear();

		if (isGameOver)
		{
			sf::Font font;
			if (!font.loadFromFile("arial.ttf"))
			{
				// Handle font loading failure
			}

			sf::Text gameOverText;
			gameOverText.setFont(font);
			gameOverText.setString("Game Over!");
			gameOverText.setCharacterSize(50);
			gameOverText.setFillColor(sf::Color::Red);
			gameOverText.setPosition(400, 300);

			window.draw(gameOverText);
		}
		else
		{
			player.draw(window);
			for (const auto& asteroid : asteroids)
			{
				asteroid.draw(window);
			}
		}

		window.display();
	}

	return EXIT_SUCCESS;
}
