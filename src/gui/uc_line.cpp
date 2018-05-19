#include "../../include/gui/uc_line.h"

UC_Line::UC_Line(int x, int y, int l, bool vertical)
{
	XPos = x;
	YPos = y;

	if(!vertical)
	{
		Width = l;
		Height = 1;
	}
	else
	{
		Width = 1;
		Height = l;
	}

    _shape.setSize(sf::Vector2f(Width, Height));
    _shape.setPosition(XPos, YPos);
    _shape.setFillColor(sf::Color(0, 0, 0));
}

UC_Line::~UC_Line()
{
	//dtor
}

void UC_Line::Draw(sf::RenderTarget *window)
{
    int posX = XPos;
    int posY = YPos;

    if(Parent != null)
    {
        posX += Parent->XPos;
        posY += Parent->YPos + Parent->Offset;
    }

	window->draw(_shape);
}
