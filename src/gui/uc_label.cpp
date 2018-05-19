#include "../../include/gui/uc_label.h"

UC_Label::UC_Label(string text, sf::Color color, int size, int x, int y)
{
	_s = new sf::Text();
	_s->setFillColor(color);

	_font = new sf::Font();
	_font->loadFromFile("res/fonts/kaliberr.ttf");

	_s->setFont(*_font);
	_s->setPosition(x, y);
	_s->setCharacterSize(size);
	_s->setString(text);

	XPos = x;
	YPos = y;
}

UC_Label::~UC_Label()
{
	delete _s;
	delete _font;
}

void UC_Label::Draw(sf::RenderTarget *window)
{
    int posX = XPos;
    int posY = YPos;

    if(Parent != null)
    {
        posX += Parent->XPos;
        posY += Parent->YPos + Parent->Offset;
    }

	_s->setPosition(posX, posY);
	window->draw(*_s);
}

void UC_Label::SetText(string text)
{
    _s->setString(text);
}

void UC_Label::SetColor(sf::Color color)
{
    _s->setFillColor(color);
}
