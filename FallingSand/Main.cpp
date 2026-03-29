#include <SFML/Graphics.hpp>
#include <vector>

#include "Simulation/Sand.h"

int main()
{
    const int width = 800;
    const int height = 600;

	SandWorld world(width, height);

    sf::RenderWindow window(sf::VideoMode(width, height), "SFML Pixel Drawing");

    // Image to store pixels
    sf::Image image;
    image.create(width, height, sf::Color::Black);

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
				world.write(event.mouseButton.x, event.mouseButton.y, SandType::Water);
            }
        }

        
		world.render(image);
        texture.update(image);
        

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}