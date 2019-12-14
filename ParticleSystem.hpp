/*
 * ParticleSystem.hpp
 *
 *  Created on: 23 paź 2019
 *      Author: kwarc
 */

#ifndef PARTICLESYSTEM_HPP_
#define PARTICLESYSTEM_HPP_

#include <SFML/Graphics.hpp>
#include <Particle.hpp>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
    ParticleSystem(unsigned int count, sf::Color color, float maxVelocity,
                   unsigned int fieldWidth, unsigned int fieldHeight, bool show);

    void follow(const std::vector<sf::Vector2f> &flowfield, float flowfieldScale);

private:
    bool show;
    unsigned int fieldWidth;
    unsigned int fieldHeight;
    float maxVelocity;

    std::vector<Particle> particles;

    // methods
    void loopInField(Particle &p);
    void limit(sf::Vector2f &vector, const sf::Vector2f &limit);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif /* PARTICLESYSTEM_HPP_ */
