#include "include/gamelogic.h"

GameLogic::GameLogic(int numPlayers, int width, int height, int numColors, bool allowRegions, bool ai)
{
    _currentPlayer = 0;
    _numPlayers = numPlayers + (ai ? 1 : 0);
    _points = new int[_numPlayers];
    _pointLabels = new UC_Label*[_numPlayers];
    _ai = ai;
    _numColors = numColors;

    _width = width;
    _height = height;

    _panelBackground = new ResizableImage("res/img/panelBackground.png", 800, 50);

    _field = new char*[height];

    for(int i = 0; i < height; i++)
    {
        _field[i] = new char[width];
    }

    _pictureBuffer = new unsigned char[height * width * 4];
    memset(_pictureBuffer, 255, height * width * 4);

    sf::Randomizer random;

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            int value = random.Random(0, numColors - 1);

            if(!allowRegions)
            {
                while(GetColor(x - 1, y, _field) == value || GetColor(x, y - 1, _field) == value)
                {
                    value = random.Random(0, numColors - 1);
                }
            }

            SetColor(x, y, value, _field);
        }
    }

    while(GetColor(0, 0, _field) == GetColor(width - 1, height - 1, _field))
    {
        int value = random.Random(0, numColors - 1);

        if(!allowRegions)
        {
            while(GetColor(width - 2, height - 1, _field) == value || GetColor(width - 1, height - 2, _field) == value)
            {
                value = random.Random(0, numColors - 1);
            }
        }

        SetColor(width - 1, height - 1, value, _field);
    }

    _image = new sf::Image(width, height, _pictureBuffer);
    _image->SetSmooth(false);
    _sprite = new sf::Sprite();
    _sprite->SetImage(*_image);

    int offsetX = (550 / _width) / 2;
    int offsetY = (550 / _height) / 2;

    _sprite->Resize(550, 550);
    _sprite->SetPosition(125 - offsetX, 0 - offsetY);

    int buttonPosition = (800 - (numColors * 50)) / 2;
    _gui = new GUI();
    _gui->Parameter = this;
    for(char i = 0; i < numColors; i++)
    {
        sf::Color color;
        color.r = DefaultPalette[(int)i][0];
        color.g = DefaultPalette[(int)i][1];
        color.b = DefaultPalette[(int)i][2];
        color.a = 255;

        UC_Button *button = new UC_Button(color, buttonPosition + (i * 50), 550, (void*)ButtonClick);

        button->callbackParam = new char;
        (*(char*)button->callbackParam) = i;

        button->secondCallbackParam = button;

        _gui->AddItem(button);
    }

    for(int i = 0; i < _numPlayers; i++)
    {
        int x = 0, y = 0;

        switch(i)
        {
        case 0:
            x = 10;
            y = 50;
            break;
        case 1:
            x = 680;
            y = 500;
            break;
        case 2:
            x = 680;
            y = 50;
            break;
        case 3:
            x = 10;
            y = 500;
            break;
        }

        _pointLabels[i] = new UC_Label("1", sf::Color(255, 255, 255), 24, x, y);
        _gui->AddItem(_pointLabels[i]);
    }

    _pointLabels[_currentPlayer]->SetColor(sf::Color(255, 255, 0));

    _gameFinished = false;
    _winner = 0;

    _clock = new sf::Clock();
}

GameLogic::~GameLogic()
{
    for(int i = 0; i < _height; i++)
    {
        delete _field[i];
    }

    delete _field;
    delete _image;
    delete _clock;
    delete _sprite;
    delete _gui;
}

char GameLogic::GetColor(int x, int y, char **field)
{
    if(x < 0 || x >= _width || y < 0 || y >= _height)
        return -1;

    return field[y][x];
}

void GameLogic::SetColor(int x, int y, char color, char **field)
{
    if(x >= _width || y >= _height)
    {
        return;
    }

    if(field == _field)
    {
        _pictureBuffer[((y * _width) + x) * 4    ] = DefaultPalette[(int)color][0];
        _pictureBuffer[((y * _width) + x) * 4 + 1] = DefaultPalette[(int)color][1];
        _pictureBuffer[((y * _width) + x) * 4 + 2] = DefaultPalette[(int)color][2];
    }

    field[y][x] = color;
}

void GameLogic::Render(sf::RenderWindow *window)
{
    _image->LoadFromPixels(_width, _height, _pictureBuffer);
    window->Draw(*_sprite);

    _panelBackground->Draw(window, 0, 550);

    _gui->DrawItems(window);
}

GUI *GameLogic::GetGui()
{
    return _gui;
}

void GameLogic::Fill(char color)
{
    bool nok = _gameFinished;

    nok |= !ColorUsable(color);

    if(!nok)
    {
        int x, y;
        GetPlayerPosition(_currentPlayer, &x, &y);

        // erst auf die entsprechende Farbe setzen damit benachbarte
        // Flächen mitgezählt werden.
        // Dann auf -2 setzen um einen eindeuten, nicht-farbwert zu haben
        // (-1 ist OutOfRegion). Danach wieder auf die Farbe setzen um zu
        // zählen.
        Fill(color, x, y, _field);
        Fill(-2, x, y, _field);
        _points[_currentPlayer] = Fill(color, x, y, _field);

        char buffer[20];
        memset(buffer, 0, 20);
        sprintf(buffer, "%d", _points[_currentPlayer]);
        _pointLabels[_currentPlayer]->SetText(buffer);

        // aktuellen Spieler zurücksetzen
        _pointLabels[_currentPlayer]->SetColor(sf::Color(255, 255, 255));

        _currentPlayer++;

        if(_currentPlayer == _numPlayers - (_ai ? 1 : 0))
        {
            if(_ai)
            {
                DoAI();
            }

            _currentPlayer = 0;
        }

        int points = 0;

        for(int i = 0; i < _numPlayers; i++)
        {
            points += _points[i];

            if(_points[i] > _points[_winner])
            {
                _winner = i;
            }
        }

        if(points == _width * _height)
        {
            _gameFinished = true;

            UC_Window *window = new UC_Window();
            window->Title = "Spiel vorbei";
            window->Width = 400;
            window->Height = 200;
            window->XPos = 200;
            window->YPos = 200;

            UC_Label *label1 = new UC_Label("Spiel vorbei", sf::Color(0, 0, 0), 48, 10, 10);
            window->Gui()->AddItem(label1);

            char buffer[200];
            sprintf(buffer, "Spieler %d hat gewonnen!\nPunkte: %d", _winner + 1, _points[_winner]);
            UC_Label *label2 = new UC_Label(buffer, sf::Color(0, 0, 0), 24, 10, 70);
            window->Gui()->AddItem(label2);

            UC_Button *button = new UC_Button("res/img/gui/button.png", "Spiel beenden", 275, 150, (void*)MainMenu::EndGame);
            window->Gui()->AddItem(button);

            _gui->AddItem(window);
        }

        // nächsten Spieler markieren
        _pointLabels[_currentPlayer]->SetColor(sf::Color(255, 255, 0));
    }
}

int GameLogic::Fill(char color, int x, int y, char **field)
{
    int points = 1;

    char oldColor = GetColor(x, y, field);

    SetColor(x, y, color, field);

    if(GetColor(x + 1, y, field) == oldColor)
        points += Fill(color, x + 1, y, field);

    if(GetColor(x - 1, y, field) == oldColor)
        points += Fill(color, x - 1, y, field);

    if(GetColor(x, y + 1, field) == oldColor)
        points += Fill(color, x, y + 1, field);

    if(GetColor(x, y - 1, field) == oldColor)
        points += Fill(color, x, y - 1, field);

    return points;
}

bool GameLogic::ColorUsable(char color)
{
    bool nok = false;

    for(int i = 0; i < _numPlayers; i++)
    {
        int x, y;
        GetPlayerPosition(i, &x, &y);

        nok |= GetColor(x, y, _field) == color;
    }

    return !nok;
}

int GameLogic::Count(char color, int x, int y)
{
    char **field = new char*[_height];

    for(int i = 0; i < _height; i++)
    {
        field[i] = new char[_width];
    }

    memcpy(field, _field, _width * _height);

    Fill(color, x, y, field);
    int points = Fill(-2, x, y, field);

    for(int i = 0; i < _height; i++)
    {
        delete field[i];
    }

    delete field;

    return points;
}

void GameLogic::DoAI()
{
    char bestColor = 0;
    int colorPoints = 0;

    int x, y;
    GetPlayerPosition(_currentPlayer, &x, &y);

    for(char color = 0; color < _numColors; color++)
    {
        if(!ColorUsable(color))
        {
            continue;
        }

        int points = Count(color, x, y);

        if(points > colorPoints)
        {
            colorPoints = points;
            bestColor = color;
        }
    }

    Fill(bestColor);
}

void GameLogic::GetPlayerPosition(int player, int *x, int *y)
{
    switch(player)
    {
    case 0:
        *x = 0;
        *y = 0;
        break;
    case 1:
        *x = _width - 1;
        *y = _height - 1;
        break;
    case 2:
        *x = _width - 1;
        *y = 0;
        break;
    case 3:
        *x = 0;
        *y = _height - 1;
        break;
    }
}

void GameLogic::ButtonClick(void *param1, void *param2)
{
    char i = *((char*)param1);
    UC_Button *sender = (UC_Button*)param2;

    GameLogic *logic = (GameLogic*)sender->Gui->Parameter;

    logic->Fill(i);
}
