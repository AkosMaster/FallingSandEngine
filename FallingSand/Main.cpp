#include <SFML/Graphics.hpp>
#include <vector>

#include "Simulation/Sand.h"

#include <chrono>
#include <thread>
int main()
{
    int gameScale = 4;
    const int width = 800;
    const int height = 800;

	int msPerFrame = 1000 / 120;

	SandWorld world(width/gameScale, height/gameScale);

    sf::RenderWindow window(sf::VideoMode(width, height), "SFML Pixel Drawing");

    // Image to store pixels
    sf::Image image;
    image.create(width/gameScale, height/gameScale, sf::Color::Black);

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite(texture);
    sprite.setScale(gameScale, gameScale);

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
                //world.write(event.mouseButton.x / gameScale, event.mouseButton.y / gameScale, SandType::Empty);
            }
        }
        

        auto update_start = std::chrono::high_resolution_clock::now();
        world.update();
        auto update_end = std::chrono::high_resolution_clock::now();

		auto update_duration = std::chrono::duration_cast<std::chrono::milliseconds>(update_end - update_start).count();
        
        if (uint16_t(update_duration) < msPerFrame) {
            std::this_thread::sleep_for(std::chrono::milliseconds( msPerFrame - update_duration ));
        }
        
        world.render(image);
        texture.update(image);
        

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}