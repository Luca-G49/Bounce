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
    constexpr float ball_radius{10.f};
    const std::string title{"Bounce"};
    sf::Color ball_color{sf::Color::Green};
    sf::Color background_color{sf::Color::Black};

    const double g{9.8}; // Gravitational acceleration [m/s²]
    double floor{550.0};          // Floor height [m]
    double scaling_factor{100.0}; // Pixel for meter

    std::vector<sf::CircleShape> balls; // Balls container
    std::vector<double> e;  // Bounce return index
    std::vector<double> v;  // Initial speed [m/s]

    sf::RenderWindow window(sf::VideoMode(width, height), title);
    sf::Font font;
    sf::Text speed_text;
    sf::Text height_text;

    sf::RectangleShape base(sf::Vector2f(width, 50));
    base.setFillColor(sf::Color::Red);
    base.setPosition(0, floor);

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
            // Mouse events
            if (event.type == sf::Event::MouseButtonPressed)
            {
                // If the left button is pressed
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::CircleShape ball(ball_radius);
                    ball.setFillColor(ball_color);
                    ball.setPosition(event.mouseButton.x - ball_radius, event.mouseButton.y - ball_radius);
                    balls.push_back(ball);

                    e.push_back(0.5);
                    v.push_back(0.0);

                    std::cout << "Spawn" << "\n";
                }
            }
        }

        // Get dt
        double dt = clock.restart().asSeconds();

        for (int i = 0; i < balls.size(); i++)
        {
            // Calculate velocity
            v[i] += g * dt; // v = v0 + g * t

            // Stops object if reached the floor with small speed
            if (((balls[i].getPosition().y + ball_radius * 2) >= floor) && (abs(v[i]) < 0.01))
            {
                v[i] = 0.0;
            }

            // Move object
            balls[i].move(0, v[i] * dt * scaling_factor);

            if ((balls[i].getPosition().y + ball_radius * 2) >= floor)
            {
                balls[i].setPosition(balls[i].getPosition().x, floor - ball_radius * 2);

                // Invert velocity with return index e
                v[i] = -v[i] * e[i];
            }
        }

        window.clear(background_color);
        for (size_t i{0}; i < balls.size(); ++i)
        {
            window.draw(balls[i]);
        }
        window.draw(base);
        window.display();
    }

    return 0;
}
