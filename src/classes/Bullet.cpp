#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

Bullet::Bullet(sf::Vector2f position, float rotation)
{
    bulletShape = sf::RectangleShape(sf::Vector2f(2.0f, 10.0f));
    bulletShape.setFillColor(sf::Color::White);
    bulletShape.setPosition(position);
    bulletShape.setRotation(rotation);
    velocity = sf::Vector2f(2.0f * std::sin(rotation * 3.14159265f / 180.0f), -std::cos(rotation * 3.14159265f / 180.0f));
    speed = 5.0f;
}

void Bullet::update()
{
    bulletShape.move(velocity * speed);
}

void Bullet::draw(sf::RenderWindow& window) const
{
    window.draw(bulletShape);
}

const sf::RectangleShape& Bullet::getBulletShape() const
{
    return bulletShape;
}
