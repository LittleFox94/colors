#include "include/gamelogic.h"

GameLogic::GameLogic(int width, int height, int numColors, bool allowRegions)
{
    _currentPlayer = 0;
    _numPlayers = 2;

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
                while(GetColor(x - 1, y) == value || GetColor(x, y - 1) == value)
                {
                    value = random.Random(0, numColors - 1);
                }
            }

            SetColor(x, y, value);
        }
    }

    while(GetColor(0, 0) == GetColor(width - 1, height - 1))
    {
        int value = random.Random(0, numColors - 1);

        if(!allowRegions)
        {
            while(GetColor(width - 2, height - 1) == value || GetColor(width - 1, height - 2) == value)
            {
                value = random.Random(0, numColors - 1);
            }
        }

        SetColor(width - 1, height - 1, value);
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
}

char GameLogic::GetColor(int x, int y)
{
    if(x < 0 || x >= _width || y < 0 || y >= _height)
        return -1;

    return _field[y][x];
}

void GameLogic::SetColor(int x, int y, char color)
{
    if(x >= _width || y >= _height)
    {
        return;
    }

    _pictureBuffer[((y * _width) + x) * 4    ] = DefaultPalette[(int)color][0];
    _pictureBuffer[((y * _width) + x) * 4 + 1] = DefaultPalette[(int)color][1];
    _pictureBuffer[((y * _width) + x) * 4 + 2] = DefaultPalette[(int)color][2];

    _field[y][x] = color;
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
    bool nok = false;

    for(int i = 0; i < _numPlayers; i++)
    {
        int x, y;
        GetPlayerPosition(i, &x, &y);

        nok |= GetColor(x, y) == color;
    }

    if(!nok)
    {
        int x, y;
        GetPlayerPosition(_currentPlayer, &x, &y);

        Fill(color, x, y);

        _currentPlayer++;

        if(_currentPlayer == _numPlayers)
        {
            _currentPlayer = 0;
        }
    }
}

void GameLogic::Fill(char color, int x, int y)
{
    char oldColor = GetColor(x, y);

    SetColor(x, y, color);

    if(GetColor(x + 1, y) == oldColor)
        Fill(color, x + 1, y);

    if(GetColor(x - 1, y) == oldColor)
        Fill(color, x - 1, y);

    if(GetColor(x, y + 1) == oldColor)
        Fill(color, x, y + 1);

    if(GetColor(x, y - 1) == oldColor)
        Fill(color, x, y - 1);
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
