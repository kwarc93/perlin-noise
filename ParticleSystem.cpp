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

ParticleSystem::ParticleSystem(unsigned int count, sf::Color color, float max_velocity,
                               unsigned int field_width, unsigned int field_height, bool show)
{
    field_width_ = field_width;
    field_height_ = field_height;
    max_velocity_ = max_velocity;
    show_ = show;

    // create particles vector with random position & velocity
    particles_.reserve(count);

    for (unsigned int i = 0; i < count; i++)
    {
        sf::Vector2f random_velocity = sf::Vector2f(max_velocity_ * (float(std::rand()) / RAND_MAX),
                                                    max_velocity_ * (float(std::rand()) / RAND_MAX));
        sf::Vector2f random_position = sf::Vector2f(std::rand() % field_width, std::rand() % field_height);

        particles_.push_back(Particle(random_position, random_velocity, color));
    }
}

void ParticleSystem::follow_flowfield(const std::vector<sf::Vector2f> &flowfield, float ff_scale)
{
    for (auto &p : particles_)
    {
        unsigned int x = p.position.x / ff_scale;
        unsigned int y = p.position.y / ff_scale;
        unsigned int index = x * field_height_ / ff_scale + y;

        sf::Vector2f force = flowfield[index] * max_velocity_;
        sf::Vector2f max_force = sf::Vector2f(1.f, 1.f) * 0.008f;
        sf::Vector2f max_velocity = sf::Vector2f(max_velocity_, max_velocity_);

        force -= p.velocity;
        limit(force, max_force);
        p.acceleration = force;
        p.velocity += p.acceleration;
        limit(p.velocity, max_velocity);
        p.position += p.velocity;
        loop_in_field(p);
    }
}

// private

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (show_)
    {
        states.transform *= getTransform();
        states.texture = NULL;

        for (auto &p : particles_)
            target.draw(&p, 1, p.type, states);
    }
}

void ParticleSystem::loop_in_field(Particle &p)
{
    if (p.position.x > field_width_)
        p.position.x = 0.f;
    else if (p.position.x < 0.f)
        p.position.x = field_width_;

    if (p.position.y > field_height_)
        p.position.y = 0.f;
    else if (p.position.y < 0.f)
        p.position.y = field_height_;
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
