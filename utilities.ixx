module;

#include <vector>
#include <string>
#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

export module utilities; 

namespace it_3
{
    // Function to calculate the Euclidean distance between two points
    double calculate_distance(const double origin[2], const double mouse_position[2]) {
        double dx = mouse_position[0] - origin[0];
        double dy = mouse_position[1] - origin[1];
        return std::sqrt(dx * dx + dy * dy);
    }

    void init(sf::RenderWindow &window, sf::Font &font, sf::Text &distance_text) {

        window.create(sf::VideoMode(800, 600), "Distance from Origin to Mouse Position");

        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error loading font. Make sure the font file is in the 'fonts' directory." << std::endl;
        }

        distance_text.setFont(font);
        distance_text.setCharacterSize(24);
        distance_text.setFillColor(sf::Color::White);
        distance_text.setPosition(50, 550);
    }


    void process_events(sf::RenderWindow &window, bool &running) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            }
        }
    }

    void render(sf::RenderWindow &window, const double origin[2], const double mouse_position[2], double distance, sf::Text &distance_text) {
        window.clear(sf::Color::Black);

        sf::CircleShape origin_point(5);
        origin_point.setFillColor(sf::Color::Red);
        origin_point.setPosition(origin[0] - origin_point.getRadius(), origin[1] - origin_point.getRadius());

        sf::CircleShape mouse_point(5);
        mouse_point.setFillColor(sf::Color::Green);
        mouse_point.setPosition(mouse_position[0] - mouse_point.getRadius(), mouse_position[1] - mouse_point.getRadius());

        distance_text.setString(std::to_string(distance));

        window.draw(origin_point);
        window.draw(mouse_point);
        window.draw(distance_text);
        window.display();
    }

    export void app(int argc, char* argv[]){

        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " <origin_x> <origin_y>" << std::endl;
            return;
        }

        double origin[2];
        origin[0] = std::stod(argv[1]);
        origin[1] = std::stod(argv[2]);

        sf::RenderWindow window;
        sf::Font font;
        sf::Text distance_text;

        init(window, font, distance_text);

        double mouse_position[2] = {0.0, 0.0};
        double distance = 0.0;

        bool running {true};

        //Event loop
        while (running)
        {
            process_events(window,running);

            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            mouse_position[0] = static_cast<double>(mouse_pos.x);
            mouse_position[1] = static_cast<double>(mouse_pos.y);

            distance = calculate_distance(origin, mouse_position);

            render(window,origin,mouse_position,distance,distance_text);
        }
        

    }
    
} // namespace it_3




