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
    UC_Label *titleLabel = new UC_Label("Colors", sf::Color(0, 0, 0), 80, 40, -7);
    _mainMenu->AddItem(titleLabel);

    UC_Line *titleUnderline = new UC_Line(40, 80, 250, false);
    _mainMenu->AddItem(titleUnderline);

    UC_Button *singlePlayerButton = new UC_Button("res/img/gui/bigButton.png", "Einzelspieler", 5, 100, NULL);
    _mainMenu->AddItem(singlePlayerButton);

    UC_Button *multiPlayerLocalButton = new UC_Button("res/img/gui/bigButton.png", "Mehrspieler (Lokal)", 5, 155, NULL);
    _mainMenu->AddItem(multiPlayerLocalButton);

    UC_Button *multiPlayerNetworkButton = new UC_Button("res/img/gui/bigButton.png", "Netzwerkspiel", 5, 210, NULL);
    _mainMenu->AddItem(multiPlayerNetworkButton);

    UC_Button *exitButton = new UC_Button("res/img/gui/bigButton.png", "Beenden", 5, height - 55, (void*)ExitButtonClickHandler);
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
