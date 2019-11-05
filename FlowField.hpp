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
    float get_scale();

private:

    bool show_;
    float scale_;
    unsigned int width_, cell_width_, height_, cell_height_;

    std::vector<sf::Vector2f> flowfield_;
    std::vector<sf::RectangleShape> vectors_;

    PerlinNoise perlin_;
    float x_off_, y_off_, z_off_;

    // methods
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};



#endif /* FLOWFIELD_HPP_ */
