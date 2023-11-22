#include "classes/Asteroid.h"
#include "classes/Player.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

bool isGameOver = false;

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(1200, 800), "Asteroids", sf::Style::Default);
	window.setFramerateLimit(60);

	Player player(window);
	std::vector<Asteroid> asteroids;

	sf::Clock asteroidSpawnTimer;
	float asteroidSpawnInterval = 2.0f;

	// Example: Add some initial asteroids
	asteroids.push_back(Asteroid::createRandomAsteroid(window, player));
	asteroids.push_back(Asteroid::createRandomAsteroid(window, player));

	// Load font outside the loop
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// Handle font loading failure
	}

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
					// Check if the player is out of lives
					if (player.getLives() <= 0)
					{
						isGameOver = true;
					}
				}
			}

			for (size_t i = 0; i < player.getBullets().size(); i++)
			{

				Bullet& bullet = player.getBullets()[i];

				bullet.update();
				bullet.draw(window);

				// Check if the bullet is out of bounds or hit an asteroid
				for (auto& asteroid : asteroids)
				{
					if (bullet.isActive() && asteroid.isCollidingWith(bullet.getBulletShape().getGlobalBounds()))
					{
						asteroid.destroy();
						bullet.deactivate();
					}
				}
			}
		}

		window.clear();

		// Display remaining lives
		sf::Text livesText;
		livesText.setFont(font); // Set the font for the lives text
		livesText.setString("Lives: " + std::to_string(player.getLives()));
		livesText.setCharacterSize(30);
		livesText.setFillColor(sf::Color::White);
		livesText.setPosition(10, 10);

		if (isGameOver)
		{
			sf::Text gameOverText;
			gameOverText.setFont(font);
			gameOverText.setString("Game Over!");
			gameOverText.setCharacterSize(50);
			gameOverText.setFillColor(sf::Color::Red);
			gameOverText.setPosition(400, 300);

			window.draw(gameOverText);

			// Display "Play Again" button
			sf::Text playAgainText;
			playAgainText.setFont(font);
			playAgainText.setString("Play Again");
			playAgainText.setCharacterSize(30);
			playAgainText.setFillColor(sf::Color::White);
			playAgainText.setPosition(430, 410); // Adjusted position

			sf::RectangleShape playAgainButton(sf::Vector2f(200, 50));
			playAgainButton.setPosition(400, 400);

			// Change button color when the mouse hovers over it
			if (playAgainButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
			{
				playAgainButton.setFillColor(sf::Color(100, 100, 255)); // Light blue when hovered
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					// Restart the game
					player.resetGame();
					isGameOver = false;
					asteroids.clear(); // Clear existing asteroids
				}
			}
			else
			{
				playAgainButton.setFillColor(sf::Color(70, 70, 200)); // Dark blue when not hovered
			}

			window.draw(playAgainButton);
			window.draw(playAgainText);
		}

		// Draw remaining lives
		else
		{
			player.draw(window);
			for (const auto& asteroid : asteroids)
			{
				asteroid.draw(window);
			}
		}

		window.draw(livesText); // Draw lives text outside the condition
		window.display();
	}

	return EXIT_SUCCESS;
}
