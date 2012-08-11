#include <SFML/Graphics.hpp>
#include "include/mainmenu.h"

int main(int argc, char *argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Colors"/*, sf::Style::Fullscreen*/);

    sf::Image *background = new sf::Image();
    background->LoadFromFile("res/img/background.png");
    sf::Sprite *backgroundSprite = new sf::Sprite();
    backgroundSprite->SetImage(*background);

    MainMenu::Initialize(&window);

    // Start the game loop
    while (window.IsOpened() && MainMenu::Running())
    {
        // Process events
        sf::Event event;
        while (window.GetEvent(event))
        {
            // Close window : exit
            if (event.Type == sf::Event::Closed)
                window.Close();

            MainMenu::DoEvents(&window, event);
        }

        // Clear screen
        window.Clear();

        window.Draw(*backgroundSprite);
        MainMenu::Draw(&window);

        // Update the window
        window.Display();
    }

    return EXIT_SUCCESS;
}
