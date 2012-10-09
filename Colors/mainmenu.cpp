#include "include/mainmenu.h"

int MainMenu::_mouseX;
int MainMenu::_mouseY;
bool MainMenu::_mouseLeftDown;
bool MainMenu::_inGame;
bool MainMenu::_running;
bool MainMenu::_closeNewGameForm;
bool MainMenu::_endGame;
GUI *MainMenu::_mainMenu;
NewGameForm *MainMenu::_newGameWindow;
GameLogic *MainMenu::_logic;
sf::String *MainMenu::_fps;

void MainMenu::Initialize(sf::RenderWindow *window)
{
    _mouseX = 0;
    _mouseY = 0;
    _inGame = false;
    _running = true;
    _mouseLeftDown = false;
    _logic = null;
    _endGame = false;

    _fps = new sf::String();
    _fps->SetFont(sf::Font::GetDefaultFont());
    _fps->SetSize(12);
    _fps->SetPosition(0, 0);
    _fps->SetColor(sf::Color(0, 0, 0));

    BuildMainMenu(window->GetWidth(), window->GetHeight());
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
            _logic->GetGui()->HoverAtPos(_mouseX, _mouseY);

            if(_mouseLeftDown)
            {
                if(!_logic->GetGui()->MoveControlAt(mouseX, mouseY, _mouseX, _mouseY) || (_mouseX == mouseX && _mouseY == mouseY))
                    _logic->GetGui()->IsMoving = false;
            }
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
            if(window->GetInput().IsMouseButtonDown(sf::Mouse::Left))
            {
                _logic->GetGui()->ClickAtPos(_mouseX, _mouseY);
                _mouseLeftDown = true;
            }
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
            if(_mouseLeftDown)
            {
                _logic->GetGui()->UnclickAtPos(_mouseX, _mouseY);
                _mouseLeftDown = false;
                _logic->GetGui()->IsMoving = false;
            }
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
            if(_logic->GetGui()->FocusedItem != null)
                _logic->GetGui()->FocusedItem->control->OnKeyPressed(event.Text.Unicode);
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

    if(_closeNewGameForm)
    {
    	_mainMenu->RemoveItem(_newGameWindow);
		delete _newGameWindow;
		_newGameWindow = null;
		_closeNewGameForm = false;
    }

    if(_endGame)
    {
        _inGame = false;
        delete _logic;
        _endGame = false;
    }
}

void MainMenu::Draw(sf::RenderWindow *target)
{
    if(_inGame)
    {
        _logic->Render(target);
    }
    else
    {
        _mainMenu->DrawItems(target);
    }

    float fps = 1.0 / target->GetFrameTime();
    char fpsLabel[50];
    sprintf(fpsLabel, "%d FPS", (int)fps);
    _fps->SetText(fpsLabel);
    target->Draw(*_fps);
}

void MainMenu::EndGame()
{
    _endGame = true;
}

void MainMenu::ExitButtonClickHandler()
{
    _running = false;
}

void MainMenu::NewSinglePlayerGameClickHandler()
{
    if(_newGameWindow == null)
    {
        _newGameWindow = new NewGameForm((void*)NewGameCancelHandler, (void*)NewGameStartHandler);
        _mainMenu->AddItem(_newGameWindow);
    }
}

void MainMenu::NewGameCancelHandler()
{
    _closeNewGameForm = true;
}

void MainMenu::NewGameStartHandler()
{
    _closeNewGameForm = true;

    _logic = new GameLogic(1, _newGameWindow->GetFieldWidth(), _newGameWindow->GetFieldHeight(), _newGameWindow->GetNumColors(), _newGameWindow->GetAllowRegions(), true);
    _inGame = true;
}
