#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

class Bullet
{
public:
	Bullet(sf::Vector2f position, float rotation)
	{
		bulletShape = sf::RectangleShape(sf::Vector2f(2.0f, 10.0f));
		bulletShape.setFillColor(sf::Color::White);
		bulletShape.setPosition(position);
		bulletShape.setRotation(rotation);
		velocity = sf::Vector2f(std::sin(rotation * 3.14159265f / 180.0f), -std::cos(rotation * 3.14159265f / 180.0f));
		speed = 5.0f;
	}

	void update()
	{
		bulletShape.move(velocity * speed);
	}

	void draw(sf::RenderWindow& window) const // Add const here
	{
		window.draw(bulletShape);
	}

private:
	sf::RectangleShape bulletShape;
	sf::Vector2f velocity;
	float speed;
};

class Player
{
public:
	Player()
	{
		// Initialize player's position, velocity, and other attributes
		// You can add more properties as needed
		playerShape = sf::ConvexShape(3);			   // Create a triangle shape
		playerShape.setPoint(0, sf::Vector2f(0, -20)); // Set the top as the front of the ship
		playerShape.setPoint(1, sf::Vector2f(-10, 10));
		playerShape.setPoint(2, sf::Vector2f(10, 10));
		playerShape.setFillColor(sf::Color::White);
		playerShape.setOrigin(0, -5);	   // Set the origin at the front of the ship
		playerShape.setPosition(400, 300); // Set the initial position
		velocity = sf::Vector2f(0, 0);	   // Initial velocity
		acceleration = 0.2f;			   // Adjust this value for desired acceleration
		maxSpeed = 5.0f;				   // Adjust this value for desired max speed
		rotationSpeed = 3.0f;			   // Adjust this value for desired rotation speed
		teleportCooldown.restart();
		shootingTimer.restart();
		shootDelay = 0.25f; // 0.25 seconds delay between shots
	}

	void update([[maybe_unused]] sf::RenderWindow& window, [[maybe_unused]] bool isLeftKeyPressed, [[maybe_unused]] bool isRightKeyPressed, [[maybe_unused]] bool isUpKeyPressed, [[maybe_unused]] bool isSpaceKeyPressed)
	{
		// Implement player's movement and shooting logic here
		// You can use keyboard or mouse input for control

		// Apply acceleration based on arrow key input
		if (isLeftKeyPressed)
		{
			// Rotate the ship to the left
			playerShape.rotate(-rotationSpeed);
		}
		if (isRightKeyPressed)
		{
			// Rotate the ship to the right
			playerShape.rotate(rotationSpeed);
		}

		if (isUpKeyPressed)
		{
			// Calculate the direction vector for the ship's current rotation
			float radians = playerShape.getRotation() * 3.14159265f / 180.0f;
			sf::Vector2f direction(std::sin(radians), -std::cos(radians));

			// Apply acceleration in the forward direction
			velocity += direction * acceleration;
		}

		// Calculate the direction vector for the ship's current rotation
		float radians = playerShape.getRotation() * 3.14159265f / 180.0f;
		sf::Vector2f direction(std::sin(radians), -std::cos(radians));

		// Shooting logic
		if (isSpaceKeyPressed)
		{
			// Check if enough time has passed since the last shot
			if (shootingTimer.getElapsedTime().asSeconds() >= shootDelay)
			{
				// Create a new bullet at the player's position and direction
				bullets.push_back(Bullet(playerShape.getPosition(), playerShape.getRotation()));

				// Restart the shooting timer
				shootingTimer.restart();
			}
		}

		// Apply damping to simulate space friction (optional)
		// velocity *= damping

		float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
		if (speed > maxSpeed)
		{
			velocity *= maxSpeed / speed;
		}

		// Update position based on velocity
		playerShape.move(velocity);

		// Implement screen wrapping
		sf::Vector2f position = playerShape.getPosition();
		if (position.x < 0)
		{
			playerShape.setPosition(window.getSize().x, position.y);
		}
		else if (position.x > window.getSize().x)
		{
			playerShape.setPosition(0, position.y);
		}
		if (position.y < 0)
		{
			playerShape.setPosition(position.x, window.getSize().y);
		}
		else if (position.y > window.getSize().y)
		{
			playerShape.setPosition(position.x, 0);
		}

		// Update bullets
		for (auto& bullet : bullets)
		{
			bullet.update();
		}
	}

	void draw([[maybe_unused]] sf::RenderWindow& window)
	{
		// Render the player's shape on the window
		window.draw(playerShape);

		for (const auto& bullet : bullets)
		{
			bullet.draw(window);
		}
	}

	void teleportToRandomLocation(sf::RenderWindow& window)
	{
		// Check if the cooldown time has passed (5 seconds)
		if (teleportCooldown.getElapsedTime().asSeconds() >= 5.0f)
		{
			// Generate random coordinates within the window's bounds
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float> xDist(0.0f, static_cast<float>(window.getSize().x));
			std::uniform_real_distribution<float> yDist(0.0f, static_cast<float>(window.getSize().y));

			// Set the player's position to the random coordinates
			playerShape.setPosition(xDist(gen), yDist(gen));

			// Restart the cooldown timer
			teleportCooldown.restart();
		}
		else
		{
			return;
		}
	}

private:
	sf::ConvexShape playerShape; // Shape representing the player
	sf::Vector2f velocity;		 // Player's velocity
	float acceleration;			 // Acceleration factor
	float maxSpeed;				 // Maximum speed
	float rotationSpeed;		 // Rotation speed
	sf::Clock teleportCooldown;
	std::vector<Bullet> bullets;
	sf::Clock shootingTimer;
	float shootDelay;
};

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(1200, 800), "Asteroids", sf::Style::Default);
	window.setFramerateLimit(60);
	window.clear(sf::Color::Black); // Set the background color to black

	Player player; // Create the player object

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

		// Collect input states at the beginning of the frame
		bool isLeftKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		bool isRightKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
		bool isUpKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		bool isSpaceKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		bool isDownKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

		if (isDownKeyPressed)
		{
			// Teleport the player to a random location
			player.teleportToRandomLocation(window);
		}
		else
		{
			// Update player's movement and shooting based on input states
			player.update(window, isLeftKeyPressed, isRightKeyPressed, isUpKeyPressed, isSpaceKeyPressed);
		}

		window.clear(); // Clear the window (clears to the background color)

		// Draw game objects, including the player's shape
		player.draw(window);

		window.display();
	}

	return EXIT_SUCCESS;
}
