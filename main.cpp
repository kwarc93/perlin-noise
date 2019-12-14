
#include <cmath>
#include <thread>
#include <chrono>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <ParticleSystem.hpp>
#include <FlowField.hpp>

int main()
{
    // seed the rng
    srand(time(0));

    // some config variables
    const int windowWidth = 640;
    const int windowHeight = 640;
    const unsigned int particlesCount = 6400;
    const bool showParticles = true;
    const bool showFlowfield = false;
    const sf::Color backgroundColor = sf::Color::White;
    const sf::Color flowfieldColor = sf::Color(0, 0, 0, 100);
    const sf::Color particlesColor = sf::Color(0, 0, 0, showFlowfield ? 255 : 2);

    // create particle system
    ParticleSystem particles = ParticleSystem(particlesCount, particlesColor, 1, windowWidth, windowHeight, showParticles);

    // create flow field
    FlowField flowfield = FlowField(windowWidth, windowHeight, 10.f, flowfieldColor, showFlowfield);

    // create window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Smoke");
    window.setVerticalSyncEnabled(true);
    window.clear(backgroundColor);

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            window.clear(backgroundColor);
        }

        // process
        particles.follow(flowfield.generate(), flowfield.getScale());

        // draw
        if (showFlowfield)
        {
            window.clear(backgroundColor);
            window.draw(flowfield);
        }

        if (showParticles)
        {
            window.draw(particles);
        }

        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}
