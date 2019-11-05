/*
 * FlowField.cpp
 *
 *  Created on: 24 paź 2019
 *      Author: kwarc
 */

#include <ctime>

#include "FlowField.hpp"

FlowField::FlowField(unsigned int width, unsigned int height, float scale, sf::Color color, bool show)
{
    // initialize flowfield parameters
    width_= floor(width / scale);
    cell_width_ = floor(width / width_);
    height_ = floor(height / scale);
    cell_height_ = floor(height / height_);
    scale_ = scale;
    show_ = show;
    x_off_ = y_off_ = z_off_ = 0.f;

    // create perlin noise object with seed
    perlin_ = PerlinNoise(time(0));

    // create flowfields cells matrix
    flowfield_.reserve(width_ * height_);
    for (unsigned int i = 0; i < width_ * height_; i++)
        flowfield_.push_back(sf::Vector2f(0.f,0.f));

    // create vectors (for flowfield visualization)
    vectors_.reserve(width_ * height_);
    for (unsigned int i = 0; i < width_ * height_; i++)
    {
        vectors_.push_back(sf::RectangleShape());
        vectors_[i].setOrigin(sf::Vector2f(cell_width_ / 2.f, 1.f));
        vectors_[i].setSize(sf::Vector2f(cell_width_, 2.f));
        vectors_[i].setPosition(sf::Vector2f(floor(i / height_) * scale + cell_width_ / 2.f,
                                             floor(i % height_) * scale + cell_height_ / 2.f));
        vectors_[i].setFillColor(color);
    }
}

const std::vector<sf::Vector2f> & FlowField::generate()
{
    const float z_inc = 0.001f;
    const float xy_inc = 0.06f;

    x_off_ = 0;
    for (unsigned int x = 0; x < width_; x++)
    {
        y_off_ = 0;
        for (unsigned int y = 0; y < height_; y++)
        {
            float angle = perlin_.noise(x_off_, y_off_, z_off_) * 2.f * M_PI * 2.f;
            unsigned int index = x * height_ + y;

            flowfield_[index] = sf::Vector2f(std::cos(angle), std::sin(angle));
            vectors_[index].setRotation(angle * 180.f / M_PI);

            y_off_ += xy_inc;
        }

        x_off_ += xy_inc;
    }

    z_off_ += z_inc;

    return flowfield_;
}

float FlowField::get_scale()
{
    return scale_;
}

// private

void FlowField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (show_)
    {
        states.transform *= getTransform();
        states.texture = NULL;

        for (auto &element : vectors_)
            target.draw(element, states);
    }
}
