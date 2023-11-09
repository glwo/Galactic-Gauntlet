#include <SFML/Graphics.hpp>
#include "classes/Player.h"

int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(1200, 800), "Asteroids", sf::Style::Default);
    window.setFramerateLimit(60);
    window.clear(sf::Color::Black);

    Player player(window); // Create the player object

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
        
        window.clear();
        player.draw(window);
        window.display();
    }

    return EXIT_SUCCESS;
}

