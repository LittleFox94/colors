#include <SFML/Graphics.hpp>
#include "../include/mainmenu.h"

int main(int argc, char *argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Colors", 0);
    window.setFramerateLimit(60);

    sf::Texture *background = new sf::Texture();
    background->loadFromFile("res/img/background.png");
    background->setSmooth(false);
    sf::Sprite *backgroundSprite = new sf::Sprite();
    backgroundSprite->setTexture(*background);

    MainMenu::Initialize(&window);

    // Start the game loop
    while (window.isOpen() && MainMenu::Running())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();

            MainMenu::DoEvents(&window, event);
        }

        // Clear screen
        window.clear();

        window.draw(*backgroundSprite);
        MainMenu::Draw(&window);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
