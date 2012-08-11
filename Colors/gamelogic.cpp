#include "include/gamelogic.h"

GameLogic::GameLogic(int width, int height, int numColors)
{
    _width = width;
    _height = height;
    _clock = new sf::Clock();

    _field = new char*[height];

    for(int i = 0; i < height; i++)
    {
        _field[i] = new char[width];
    }

	_pictureBuffer = new unsigned char[height * width * 4];

    sf::Randomizer random;

    for(int y = 0; y < height; y++)
    {
    	char *line = _field[y];

    	for(int x = 0; x < width; x++)
    	{
    		line[x] = (char)random.Random(0, numColors - 1);

    		_pictureBuffer[((y * width) + x) * 4    ] = DefaultPalette[(int)line[x]][0];
    		_pictureBuffer[((y * width) + x) * 4 + 1] = DefaultPalette[(int)line[x]][1];
    		_pictureBuffer[((y * width) + x) * 4 + 2] = DefaultPalette[(int)line[x]][2];
    		_pictureBuffer[((y * width) + x) * 4 + 3] = 255;
    	}
    }

    _image = new sf::Image(width, height, _pictureBuffer);
    _image->SetSmooth(false);
    _sprite = new sf::Sprite();
    _sprite->SetImage(*_image);
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
	return _field[y][x];
}

void GameLogic::SetColor(int x, int y, char color)
{
	if(x >= _width || y >= _height)
	{
		return;
	}

	_pictureBuffer[((y * _width) + x) * 3    ] = DefaultPalette[(int)color][0];
	_pictureBuffer[((y * _width) + x) * 3 + 1] = DefaultPalette[(int)color][1];
	_pictureBuffer[((y * _width) + x) * 3 + 2] = DefaultPalette[(int)color][2];

	_field[y][x] = color;
}

void GameLogic::Render(sf::RenderWindow *window)
{
    int offsetX = (550 / _width) / 2;
    int offsetY = (550 / _height) / 2;

    _sprite->Resize(550, 550);
    _sprite->SetPosition(125 - offsetX, 0 - offsetY);
    window->Draw(*_sprite);
}
