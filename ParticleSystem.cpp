/*
 * ParticleSystem.cpp
 *
 *  Created on: 23 paź 2019
 *      Author: kwarc
 */

#include <random>
#include <cmath>
#include <ctime>
#include <iostream>

#include "ParticleSystem.hpp"

namespace
{
    float rnd(void) { return float(std::rand()) / RAND_MAX; }
}

ParticleSystem::ParticleSystem(unsigned int count, sf::Color color, float maxVelocity,
                               unsigned int fieldWidth, unsigned int fieldHeight, bool show)
{
    this->fieldWidth = fieldWidth;
    this->fieldHeight = fieldHeight;
    this->maxVelocity = maxVelocity;
    this->show = show;

    // create particles vector with random position & velocity
    this->particles.reserve(count);

    for (unsigned int i = 0; i < count; i++)
    {
        sf::Vector2f randomVelocity = sf::Vector2f(this->maxVelocity * rnd(),
                                                   this->maxVelocity * rnd());
        sf::Vector2f randomPosition = sf::Vector2f(std::rand() % fieldWidth, std::rand() % fieldHeight);

        this->particles.push_back(Particle(randomPosition, randomVelocity, color));
    }
}

void ParticleSystem::follow(const std::vector<sf::Vector2f> &flowfield, float flowfieldScale)
{
    for (auto &p : this->particles)
    {
        unsigned int x = p.position.x / flowfieldScale;
        unsigned int y = p.position.y / flowfieldScale;
        unsigned int index = x * this->fieldHeight / flowfieldScale + y;

        sf::Vector2f force = flowfield[index] * this->maxVelocity;
        sf::Vector2f max_force = sf::Vector2f(1, 1) * (rnd() * 0.004f + 0.006f);
        sf::Vector2f max_velocity = sf::Vector2f(this->maxVelocity, this->maxVelocity);

        force -= p.velocity;
        limit(force, max_force);

        p.acceleration = force;

        p.velocity += p.acceleration;
        limit(p.velocity, max_velocity);

        p.position += p.velocity;

        loopInField(p);
    }
}

// private

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (show)
    {
        states.transform *= getTransform();
        states.texture = NULL;

        for (auto &p : this->particles)
            target.draw(&p, 1, p.type, states);
    }
}

void ParticleSystem::loopInField(Particle &p)
{
    if (p.position.x > this->fieldWidth)
        p.position.x = 0.f;
    else if (p.position.x < 0.f)
        p.position.x = this->fieldWidth;

    if (p.position.y > this->fieldHeight)
        p.position.y = 0.f;
    else if (p.position.y < 0.f)
        p.position.y = this->fieldHeight;
}

void ParticleSystem::limit(sf::Vector2f &vector, const sf::Vector2f &limit)
{
    if (vector.x > limit.x)
        vector.x = limit.x;
    else if (vector.x < -limit.x)
        vector.x = -limit.x;

    if (vector.y > limit.y)
        vector.y = limit.y;
    else if (vector.y < -limit.y)
        vector.y = -limit.y;
}
