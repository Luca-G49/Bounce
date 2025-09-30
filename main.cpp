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
    const double e{0.5};          // bounce return index
    double v{0.0};                // Initial speed [m/s]
    double h{4.0};                // initial height [m]
    double floor{550.0};          // Floor height [m]
    double scaling_factor{100.0}; // Pixel for meter

    sf::RenderWindow window(sf::VideoMode(width, height), title);
    sf::Font font;
    sf::Text speed_text;
    sf::Text height_text;

    sf::RectangleShape base(sf::Vector2f(width, 50));
    base.setFillColor(sf::Color::Red);
    base.setPosition(0, floor);

    sf::CircleShape ball(ball_radius);
    ball.setFillColor(ball_color);
    ball.setPosition((width / 2) - ball_radius, 0);

    if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error loading font. Make sure the font file is in the 'fonts' directory." << std::endl;
    }

    speed_text.setFont(font);
    speed_text.setCharacterSize(16);
    speed_text.setFillColor(sf::Color::White);
    speed_text.setPosition(0, 0);

    // Timer setup
    sf::Clock clock;

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

        double dt = clock.restart().asSeconds();

        // Calculate velocity
        v += g * dt; // v = v0 + g * t

        ball.move(0, v * dt * scaling_factor);

        if ((ball.getPosition().y + ball_radius * 2) >= floor)
        {
            ball.setPosition(ball.getPosition().x, floor - ball_radius * 2);

            // Invert velocity with return index e
            v = -v * e;

            // Stop
            if(abs(v) < 0.01){
                v = 0.0;
            }
        }

        speed_text.setString(std::to_string(v) + " m/s");

        window.clear(background_color);
        window.draw(ball);
        window.draw(base);
        window.draw(speed_text);
        window.display();
    }

    return 0;
}
