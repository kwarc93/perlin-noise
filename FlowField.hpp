/*
 * FlowField.hpp
 *
 *  Created on: 24 paź 2019
 *      Author: kwarc
 */

#ifndef FLOWFIELD_HPP_
#define FLOWFIELD_HPP_

#include <SFML/Graphics.hpp>
#include <PerlinNoise.hpp>

class FlowField : public sf::Drawable, public sf::Transformable
{
public:

    FlowField(unsigned int width, unsigned int height, float scale, sf::Color color, bool show);

    const std::vector<sf::Vector2f> & generate();
    float getScale() const;

private:

    bool show;
    float scale;
    unsigned int width, height;
    unsigned int cellWidth, cellHeight;

    std::vector<sf::Vector2f> flowfield;
    std::vector<sf::RectangleShape> vectors;

    struct dimensions
    {
        float x, y, z;
    };

    struct dimensions noiseDimensions;
    PerlinNoise noiseGenerator;

    // methods
    float calculateAngle(void);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif /* FLOWFIELD_HPP_ */
