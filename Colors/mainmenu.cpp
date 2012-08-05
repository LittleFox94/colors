#include "include/mainmenu.h"

int MainMenu::_mouseX;
int MainMenu::_mouseY;
bool MainMenu::_mouseLeftDown;
bool MainMenu::_inGame;
bool MainMenu::_running;
bool MainMenu::_closeNewGameForm;
GUI *MainMenu::_mainMenu;
UC_Window *MainMenu::_newGameWindow;

void MainMenu::Initialize(sf::RenderWindow *window)
{
    _mouseX = 0;
    _mouseY = 0;
    _inGame = false;
    _running = true;
    _mouseLeftDown = false;

    BuildMainMenu(window->GetWidth(), window->GetHeight());
    BuildNewGameWindow();
}

void MainMenu::BuildMainMenu(int width, int height)
{
    _mainMenu = new GUI();

    UC_Label *titleLabel = new UC_Label("Colors", sf::Color(0, 0, 0), 80, 40, -7);
    _mainMenu->AddItem(titleLabel);

    UC_Line *titleUnderline = new UC_Line(40, 80, 250, false);
    _mainMenu->AddItem(titleUnderline);

    UC_Button *singlePlayerButton = new UC_Button("res/img/gui/bigButton.png", "Einzelspieler", 5, 100, (void*)NewSinglePlayerGameClickHandler);
    _mainMenu->AddItem(singlePlayerButton);

    UC_Button *multiPlayerLocalButton = new UC_Button("res/img/gui/bigButton.png", "Mehrspieler", 5, 155, NULL);
    _mainMenu->AddItem(multiPlayerLocalButton);

    UC_Button *multiPlayerNetworkButton = new UC_Button("res/img/gui/bigButton.png", "Netzwerkspiel", 5, 210, NULL);
    _mainMenu->AddItem(multiPlayerNetworkButton);

    UC_Button *exitButton = new UC_Button("res/img/gui/bigButton.png", "Beenden", 5, height - 55, (void*)ExitButtonClickHandler);
    _mainMenu->AddItem(exitButton);
}

void MainMenu::BuildNewGameWindow()
{
    _newGameWindow = new NewGameForm((void*)NewGameCancelHandler);
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
    {
        int mouseX = window->GetInput().GetMouseX();
        int mouseY = window->GetInput().GetMouseY();

        if(_inGame)
        {
        }
        else
        {
            _mainMenu->HoverAtPos(_mouseX, _mouseY);

            if(_mouseLeftDown)
            {
                if(!_mainMenu->MoveControlAt(mouseX, mouseY, _mouseX, _mouseY) || (_mouseX == mouseX && _mouseY == mouseY))
                    _mainMenu->IsMoving = false;
            }
        }

        _mouseX = mouseX;
        _mouseY = mouseY;
    }
    break;

    case sf::Event::MouseButtonPressed:
        if(_inGame)
        {
        }
        else
        {
            if(window->GetInput().IsMouseButtonDown(sf::Mouse::Left))
            {
                _mainMenu->ClickAtPos(_mouseX, _mouseY);
                _mouseLeftDown = true;
            }
        }
        break;

    case sf::Event::MouseButtonReleased:
        if(_inGame)
        {
        }
        else
        {
            if(_mouseLeftDown)
            {
                _mainMenu->UnclickAtPos(_mouseX, _mouseY);
                _mouseLeftDown = false;
                _mainMenu->IsMoving = false;
            }
        }
        break;

    case sf::Event::KeyPressed:
        if(_inGame)
        {
        }
        else
        {
            if(_mainMenu->FocusedItem != null)
                _mainMenu->FocusedItem->control->OnKeyPressed(event.Text.Unicode);
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

void MainMenu::NewSinglePlayerGameClickHandler()
{
    _mainMenu->RemoveItem(_newGameWindow);
    _mainMenu->AddItem(_newGameWindow);
}

void MainMenu::NewGameCancelHandler()
{
    _mainMenu->RemoveItem(_newGameWindow);
}
