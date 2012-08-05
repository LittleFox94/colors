#include "../include/gui/uc_label.h"

UC_Label::UC_Label(string text, sf::Color color, int size, int x, int y)
{
	_s.SetColor(color);

	_font = sf::Font();
	_font.LoadFromFile("res/fonts/kaliberr.ttf", size);

	_s.SetFont(_font);
	_s.SetPosition(x, y);
	_s.SetSize(size);
	_s.SetText(text);

	XPos = x;
	YPos = y;
}

UC_Label::~UC_Label()
{
}

void UC_Label::Dispose()
{
	_s.~Drawable();
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

	_s.SetPosition(posX, posY);
	window->Draw(_s);
}
