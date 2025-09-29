#include <vector>
#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <iostream>

import utilities;

int main(int argc, char *argv[])
{

    // Store data in pre-defined variable
    constexpr int width{800};
    constexpr int height{600};
    constexpr float ball_radius{40.f};
    const std::string title{"Bounce"};
    sf::Color ball_color{sf::Color::Green};
    sf::Color background_color{sf::Color::Black};

    const double g{9.8};          // Gravitational acceleration [m/s²]
    const double e{0.8};          // bounce return index
    double v{0.0};                // Initial speed [m/s]
    double h{4.0};                // initial height [m]
    double scaling_factor{100.0}; // Pixel for meter

    sf::RenderWindow window(sf::VideoMode(width, height), title);

    sf::RectangleShape base(sf::Vector2f(width, 50));
    base.setFillColor(sf::Color::Red);
    base.setPosition(0,550);

    sf::CircleShape ball(ball_radius);
    ball.setFillColor(ball_color);
    ball.setPosition((width / 2) - ball_radius, 0);

    // Timer setup
    sf::Clock clock;
    constexpr float interval {1.0f}; // every 50 milliseconds

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Key Events
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
        }

        // Timer based movement
        if (clock.getElapsedTime().asMilliseconds() > interval)
        {
            v += g * scaling_factor * interval / 1000; // v = v0 + g * t
            if ((ball.getPosition().y + ball_radius * 2) < 550.0f){
                ball.move(0.0,v * interval / 1000.0);
            }

            clock.restart();
        }

        window.clear(background_color);
        window.draw(ball);
        window.draw(base);
        window.display();
    }

    return 0;
}
