#include "include/mainmenu.h"

int MainMenu::_mouseX;
int MainMenu::_mouseY;
bool MainMenu::_inGame;
bool MainMenu::_running;
GUI *MainMenu::_mainMenu;

void MainMenu::Initialize(sf::RenderWindow *window)
{
    _mouseX = 0;
    _mouseY = 0;
    _inGame = false;
    _running = true;

    _mainMenu = new GUI();
    BuildMainMenu(window->GetWidth(), window->GetHeight());
}

void MainMenu::BuildMainMenu(int width, int height)
{
    UC_Button *exitButton = new UC_Button("res/img/gui/button.png", "Beenden", width - 125, height - 30, (void*)ExitButtonClickHandler);
    _mainMenu->AddItem(exitButton);
}

bool MainMenu::Running()
{
    return _running;
}

void MainMenu::DoEvents(sf::RenderWindow *window, sf::Event event)
{
    switch(event.Type)
    {
        case sf::Event::MouseMoved:
            _mouseX = window->GetInput().GetMouseX();
            _mouseY = window->GetInput().GetMouseY();

            if(_inGame)
            {
            }
            else
            {
                _mainMenu->HoverAtPos(_mouseX, _mouseY);
            }
            break;

        case sf::Event::MouseButtonPressed:
            if(_inGame)
            {
            }
            else
            {
                _mainMenu->ClickAtPos(_mouseX, _mouseY);
            }
            break;

        case sf::Event::MouseButtonReleased:
            if(_inGame)
            {
            }
            else
            {
                _mainMenu->UnclickAtPos(_mouseX, _mouseY);
            }
            break;

        default:
            break;
    }
}

void MainMenu::Draw(sf::RenderTarget *target)
{
    if(_inGame)
    {
    }
    else
    {
        _mainMenu->DrawItems(target);
    }
}

void MainMenu::ExitButtonClickHandler()
{
    _running = false;
}
