#include "classes/Asteroid.h"
#include "classes/HighScoreManager.h"
#include "classes/Player.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

bool isGameOver = false;
bool scoreNeedsUpdate = true;
bool enteringName = false;

void GameOver(sf::RenderWindow& window, Player& player, HighScoreManager& highScoreManager, std::string& playerName);

void GameOver(sf::RenderWindow& window, Player& player, HighScoreManager& highScoreManager, std::string& playerName)
{
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// Handle font loading failure
	}

	if (scoreNeedsUpdate)
	{
		highScoreManager.addScore(playerName, player.getScore());
		scoreNeedsUpdate = false; // Set the flag to false once the score is updated
	}

	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setString("Game Over!");
	gameOverText.setCharacterSize(50);
	gameOverText.setFillColor(sf::Color::Red);

	sf::FloatRect textRect = gameOverText.getLocalBounds();
	gameOverText.setPosition(window.getSize().x / 2 - textRect.width / 2, 300);

	sf::Text highScoresText;
	highScoresText.setFont(font);
	highScoresText.setCharacterSize(30);
	highScoresText.setFillColor(sf::Color::White);

	const std::vector<std::pair<std::string, int>>& scores = highScoreManager.getScores();
	if (!scores.empty())
	{
		std::string displayText = "High Scores:\n";
		for (size_t i = 0; i < scores.size(); ++i)
		{
			displayText += std::to_string(i + 1) + ". " + scores[i].first + ": " + std::to_string(scores[i].second) + "\n";
		}
		highScoresText.setString(displayText);
	}

	textRect = highScoresText.getLocalBounds();
	highScoresText.setPosition(window.getSize().x / 2 - textRect.width / 2, 350);

	window.draw(gameOverText);
	window.draw(highScoresText);

	if (!enteringName)
	{
		sf::Text enterNameText;
		enterNameText.setFont(font);
		enterNameText.setString("Press Enter to enter your name!");
		enterNameText.setCharacterSize(20);
		enterNameText.setFillColor(sf::Color::White);

		textRect = enterNameText.getLocalBounds();
		enterNameText.setPosition(window.getSize().x / 2 - textRect.width / 2, 450);

		window.draw(enterNameText);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			enteringName = true;
		}
	}
	else
	{
		sf::Text playerNameText;
		playerNameText.setFont(font);
		playerNameText.setCharacterSize(30);
		playerNameText.setFillColor(sf::Color::White);
		playerNameText.setString("Name: " + playerName);

		textRect = playerNameText.getLocalBounds();
		playerNameText.setPosition(window.getSize().x / 2 - textRect.width / 2, 500);

		window.draw(playerNameText);

		player.drawTextInput(window);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			// Player pressed Enter, finish entering the name
			enteringName = false;
		}
	}
}

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
		// bool enteringName = false;
		std::string playerName;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
			{
				if (enteringName)
				{
					// Player pressed Enter, finish entering the name
					enteringName = false;
				}
				else
				{
					// Player pressed Enter, restart the game
					highScoreManager.addScore(playerName, player.getScore());
					player.resetGame();
					isGameOver = false;
					asteroids.clear();
					playerName.clear();
				}
			}
			else if (event.type == sf::Event::TextEntered && enteringName)
			{
				// Handle text input
				player.handleTextEntered(event.text.unicode);
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
				asteroid.update(window);
				if (player.isCollidingWithAsteroid(asteroid))
				{
					player.handleAsteroidCollision(asteroid);
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

			for (size_t i = 0; i < player.getBullets().size(); i++)
			{
				Bullet& bullet = player.getBullets()[i];
				bullet.draw(window);
			}
		}

		window.clear();

		sf::Text livesText;
		livesText.setFont(font);
		livesText.setString("Lives: " + std::to_string(player.getLives()));
		livesText.setCharacterSize(30);
		livesText.setFillColor(sf::Color::White);
		livesText.setPosition(10, 10);

		sf::Text scoreText;
		scoreText.setFont(font);
		scoreText.setString("Score: " + std::to_string(player.getScore()));
		scoreText.setCharacterSize(30);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setPosition(window.getSize().x - scoreText.getLocalBounds().width - 10, 10);

		if (isGameOver)
		{
			GameOver(window, player, highScoreManager, playerName);
			// isGameOver = false;
		}

		else
		{
			player.draw(window);
			for (const auto& asteroid : asteroids)
			{
				asteroid.draw(window);
			}
			if (enteringName)
			{
				player.drawTextInput(window);
			}
		}

		window.draw(livesText);
		window.draw(scoreText);
		window.display();
		sf::sleep(sf::milliseconds(8));
	}

	return EXIT_SUCCESS;
}
