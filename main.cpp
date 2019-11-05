
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
	const int window_width = 640;
	const int window_height = 640;
	const unsigned int particles_count = 6400;
    const bool show_particles = true;
    const bool show_flowfield = false;
    const sf::Color background_color = sf::Color::White;
    const sf::Color flowfield_color = sf::Color(0, 0, 0, 100);
    const sf::Color particles_color = sf::Color(0, 0, 0, show_flowfield ? 255 : 2);

	// create particle system
    ParticleSystem particles = ParticleSystem(
    		particles_count,
			particles_color,
			1.f,
			window_width,
			window_height,
			show_particles);

    // create flow field
    FlowField flowfield = FlowField(window_width, window_height, 10.f, flowfield_color, show_flowfield);

    // create window
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Smoke");
    window.setVerticalSyncEnabled(true);
    window.clear(background_color);

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
        	window.clear(background_color);
        }

        // process
        particles.follow_flowfield(flowfield.generate(), flowfield.get_scale());

        // draw
        if (show_flowfield)
        {
        	window.clear(background_color);
        	window.draw(flowfield);
        }

        if (show_particles)
        {
        	window.draw(particles);
        }

        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}
