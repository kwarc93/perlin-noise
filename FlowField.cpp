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
    this->width = floor(width / scale);
    this->height = floor(height / scale);
    this->cellWidth = floor(width / this->width);
    this->cellHeight = floor(height / this->height);
    this->scale = scale;
    this->show = show;
    this->noiseDimensions.x = this->noiseDimensions.y = this->noiseDimensions.z = 0;

    // create perlin noise object with seed
    this->noiseGenerator = PerlinNoise(time(0));

    // create flowfields cells matrix
    this->flowfield.reserve(this->width * this->height);
    for (unsigned int i = 0; i < this->width * this->height; i++)
        this->flowfield.push_back(sf::Vector2f(0,0));

    // create vectors (for flowfield visualization)
    this->vectors.reserve(this->width * this->height);
    for (unsigned int i = 0; i < this->width * this->height; i++)
    {
        this->vectors.push_back(sf::RectangleShape());
        this->vectors[i].setOrigin(sf::Vector2f(this->cellWidth / 2.f, 1.f));
        this->vectors[i].setSize(sf::Vector2f(this->cellWidth, 2.f));
        this->vectors[i].setPosition(sf::Vector2f(floor(i / this->height) * this->scale + this->cellWidth / 2.f,
                                                  floor(i % this->height) * this->scale + this->cellHeight / 2.f));
        this->vectors[i].setFillColor(color);
    }
}

const std::vector<sf::Vector2f> & FlowField::generate()
{
    const float zStep = 0.001f;
    const float xyStep = 0.06f;

    this->noiseDimensions.x = 0;
    for (unsigned int x = 0; x < this->width; x++)
    {
        this->noiseDimensions.y = 0;

        for (unsigned int y = 0; y < this->height; y++)
        {
            float angle = calculateAngle();
            unsigned int index = x * this->height + y;

            this->flowfield[index] = sf::Vector2f(std::cos(angle), std::sin(angle));
            this->vectors[index].setRotation(angle * 180.f / M_PI);

            this->noiseDimensions.y += xyStep;
        }

        this->noiseDimensions.x += xyStep;
    }

    this->noiseDimensions.z += zStep;

    return this->flowfield;
}

float FlowField::getScale() const
{
    return this->scale;
}

// private

float FlowField::calculateAngle(void)
{
    const float factor = 2.f * M_PI * 2.f;
    return factor * this->noiseGenerator.noise(this->noiseDimensions.x,
                                               this->noiseDimensions.y,
                                               this->noiseDimensions.z);
}

void FlowField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (this->show)
    {
        states.transform *= getTransform();
        states.texture = NULL;

        for (auto &element : this->vectors)
            target.draw(element, states);
    }
}
