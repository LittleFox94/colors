#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "gui/gui.h"
#include "newgameform.h"

class MainMenu
{
    public:
        static void Initialize(sf::RenderWindow *window);
        static void DoEvents(sf::RenderWindow *window, sf::Event event);
        static void Draw(sf::RenderTarget *target);
        static bool Running();

    private:
        static void BuildMainMenu(int width, int height);
        static void BuildNewGameWindow();

        static void ExitButtonClickHandler();
        static void NewSinglePlayerGameClickHandler();
        static void NewGameCancelHandler();

        static int _mouseX;
        static int _mouseY;
        static bool _mouseLeftDown;

        static bool _inGame;
        static bool _running;
        static bool _closeNewGameForm;

        static GUI *_mainMenu;
        static UC_Window *_newGameWindow;
};

#endif // MAINMENU_H_INCLUDED
