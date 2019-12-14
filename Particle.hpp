/*
 * Particle.h
 *
 *  Created on: 14 gru 2019
 *      Author: kwarc
 */

#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_

#include <SFML/Graphics.hpp>

class Particle : public sf::Vertex
{
public:
    Particle(sf::Vector2f position, sf::Vector2f velocity, sf::Color color);

    sf::Vector2f acceleration;
    sf::Vector2f velocity;

    static const sf::PrimitiveType type = sf::Points;
};

#endif /* PARTICLE_HPP_ */
