#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "gui/gui.h"
#include "newgameform.h"
#include "gamelogic.h"

class GameLogic;

class MainMenu
{
    public:
        static void Initialize(sf::RenderWindow *window);
        static void DoEvents(sf::RenderWindow *window, sf::Event event);
        static void Draw(sf::RenderWindow *target);
        static bool Running();

        static void EndGame();

    private:
        static void BuildMainMenu(int width, int height);
        static void BuildNewGameWindow();

        static void ExitButtonClickHandler();
        static void NewSinglePlayerGameClickHandler();
        static void NewGameCancelHandler();
        static void NewGameStartHandler();

        static int _mouseX;
        static int _mouseY;
        static bool _mouseLeftDown;

        static bool _inGame;
        static bool _running;
        static bool _closeNewGameForm;
        static bool _endGame;

        static GUI *_mainMenu;
        static NewGameForm *_newGameWindow;

        static GameLogic *_logic;
};

#endif // MAINMENU_H_INCLUDED
