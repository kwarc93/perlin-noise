/*
 * Particle.cpp
 *
 *  Created on: 14 gru 2019
 *      Author: kwarc
 */

#include <Particle.hpp>

Particle::Particle(sf::Vector2f position, sf::Vector2f velocity, sf::Color color)
{
    this->position = position;
    this->velocity = velocity;
    this->acceleration = sf::Vector2f(0,0);
    this->color = color;
}
