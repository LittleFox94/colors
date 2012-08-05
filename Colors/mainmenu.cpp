#include "include/mainmenu.h"

int MainMenu::_mouseX;
int MainMenu::_mouseY;
bool MainMenu::_mouseLeftDown;
bool MainMenu::_inGame;
bool MainMenu::_running;
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

    UC_Button *singlePlayerButton = new UC_Button("res/img/gui/bigButton.png", "Einzelspieler", 5, 100, NULL);
    _mainMenu->AddItem(singlePlayerButton);

    UC_Button *multiPlayerLocalButton = new UC_Button("res/img/gui/bigButton.png", "Mehrspieler (Lokal)", 5, 155, NULL);
    _mainMenu->AddItem(multiPlayerLocalButton);

    UC_Button *multiPlayerNetworkButton = new UC_Button("res/img/gui/bigButton.png", "Netzwerkspiel", 5, 210, NULL);
    _mainMenu->AddItem(multiPlayerNetworkButton);

    UC_Button *exitButton = new UC_Button("res/img/gui/bigButton.png", "Beenden", 5, height - 55, (void*)ExitButtonClickHandler);
    _mainMenu->AddItem(exitButton);
}

void MainMenu::BuildNewGameWindow()
{
    _newGameWindow = new UC_Window();
    _newGameWindow->Width = 500;
    _newGameWindow->Height = 400;
    _newGameWindow->Title = "Neues Spiel";

    UC_Label *title = new UC_Label("Neues Spiel", sf::Color(0, 0, 0), 24, 5, 24);
    _newGameWindow->Gui()->AddItem(title);

    UC_Label *numPlayersLabel = new UC_Label("Spieleranzahl:", sf::Color(0, 0, 0), 12, 5, 72);
    _newGameWindow->Gui()->AddItem(numPlayersLabel);

    UC_ComboBox *numPlayers = new UC_ComboBox(140, 70, 120);
    numPlayers->AddItem("2");
    numPlayers->AddItem("3");
    numPlayers->AddItem("4");
    _newGameWindow->Gui()->AddItem(numPlayers);

    UC_Label *numColorsLabel = new UC_Label("Farbenanzahl:", sf::Color(0, 0, 0), 12, 5, 102);
    _newGameWindow->Gui()->AddItem(numColorsLabel);

    UC_ComboBox *numColors = new UC_ComboBox(140, 100, 120);
    numColors->AddItem("4");
    numColors->AddItem("5");
    numColors->AddItem("6");
    numColors->AddItem("7");
    numColors->AddItem("8");
    numColors->AddItem("9");
    numColors->AddItem("10");
    _newGameWindow->Gui()->AddItem(numColors);

    _mainMenu->AddItem(_newGameWindow);
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
