/*
 * ParticleSystem.hpp
 *
 *  Created on: 23 paź 2019
 *      Author: kwarc
 */

#ifndef PARTICLESYSTEM_HPP_
#define PARTICLESYSTEM_HPP_

#include <SFML/Graphics.hpp>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
    class Particle : public sf::Vertex
    {
    public:
        Particle(sf::Vector2f pos, sf::Vector2f v, sf::Color col)
        {
            position = pos;
            velocity = v;
            acceleration = sf::Vector2f(0.0, 0.0);
            color = col;
        }

        sf::Vector2f acceleration;
        sf::Vector2f velocity;

        static const sf::PrimitiveType type = sf::Points;
    };

public:

    ParticleSystem(unsigned int count, sf::Color color, float max_velocity,
                   unsigned int field_width, unsigned int field_height, bool show);

    void follow_flowfield(const std::vector<sf::Vector2f> &flowfield, float ff_scale);

private:

    bool show_;
    unsigned int field_width_;
    unsigned int field_height_;
    float max_velocity_;

    std::vector<Particle> particles_;

    // methods
    void loop_in_field(Particle &p);
    void limit(sf::Vector2f &vector, const sf::Vector2f &limit);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif /* PARTICLESYSTEM_HPP_ */
