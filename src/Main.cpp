#include "classes/Asteroid.h"
#include "classes/HighScoreManager.h"
#include "classes/Player.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

bool isGameOver = false;

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(1200, 800), "Asteroids", sf::Style::Default);
	window.setFramerateLimit(60);

	Player player(window);
	std::vector<Asteroid> asteroids;
	HighScoreManager highScoreManager;

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

		window.clear();

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
				// std::cout << "Initial Asteroid Position: " << asteroid.getPosition().x << ", " << asteroid.getPosition().y << std::endl;
				// std::cout << "Ateroid start update" << std::endl;
				asteroid.update(window);
				// std::cout << "Ateroid end update" << std::endl;
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

				// Check if the bullet is out of bounds or hit an asteroid
				for (auto& asteroid : asteroids)
				{
					if (bullet.isActive() && asteroid.isCollidingWith(bullet.getBulletShape().getGlobalBounds()))
					{
						asteroid.destroy();
						bullet.deactivate();
						player.incrementScore(10);
					}
				}
			}

			// Draw bullets in the main draw loop
			for (size_t i = 0; i < player.getBullets().size(); i++)
			{
				Bullet& bullet = player.getBullets()[i];
				bullet.draw(window);
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

		sf::Text scoreText;
		scoreText.setFont(font); // Set the font for the score text
		scoreText.setString("Score: " + std::to_string(player.getScore()));
		scoreText.setCharacterSize(30);
		scoreText.setFillColor(sf::Color::White);
		// Adjusted position for the top right
		scoreText.setPosition(window.getSize().x - scoreText.getLocalBounds().width - 10, 10);

		if (isGameOver)
		{
			sf::Text gameOverText;
			gameOverText.setFont(font);
			gameOverText.setString("Game Over!");
			gameOverText.setCharacterSize(50);
			gameOverText.setFillColor(sf::Color::Red);

			// Center the "Game Over" text
			sf::FloatRect textRect = gameOverText.getLocalBounds();
			gameOverText.setPosition(window.getSize().x / 2 - textRect.width / 2, 300);

			highScoreManager.addScore(player.getScore());
			highScoreManager.saveScores();

			// Display three highest scores
			sf::Text highScoresText;
			highScoresText.setFont(font);
			highScoresText.setCharacterSize(30);
			highScoresText.setFillColor(sf::Color::White);

			// Load scores from the manager
			const std::vector<int>& scores = highScoreManager.getScores();
			if (!scores.empty())
			{
				highScoresText.setString("High Scores:\n1. " + std::to_string(scores[0]) + "\n2. " + std::to_string(scores[1]) + "\n3. " + std::to_string(scores[2]));
			}

			// Center the high scores text
			textRect = highScoresText.getLocalBounds();
			highScoresText.setPosition(window.getSize().x / 2 - textRect.width / 2, 350);

			window.draw(gameOverText);
			window.draw(highScoresText);

			// Display "Play Again" button
			sf::Text playAgainText;
			playAgainText.setFont(font);
			playAgainText.setString("Play Again");
			playAgainText.setCharacterSize(30);
			playAgainText.setFillColor(sf::Color::White);

			// Center the "Play Again" text
			textRect = playAgainText.getLocalBounds();
			playAgainText.setPosition(window.getSize().x / 2 - textRect.width / 2, 500);

			sf::RectangleShape playAgainButton(sf::Vector2f(200, 50));
			playAgainButton.setPosition(window.getSize().x / 2 - 100, 550);

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
		window.draw(scoreText);
		window.display();
		sf::sleep(sf::milliseconds(8));
	}

	return EXIT_SUCCESS;
}
