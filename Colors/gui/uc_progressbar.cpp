#include "../include/gui/uc_progressbar.h"

UC_ProgressBar::UC_ProgressBar(int min, int max, int x, int y, int w, int h)
{
	XPos = x;
	YPos = y;
	Width = w;
	Height = h;
	min = min;
	max = max;
}

UC_ProgressBar::~UC_ProgressBar()
{
	//dtor
}

void UC_ProgressBar::Draw(sf::RenderTarget *window)
{
    int posX = XPos;
    int posY = YPos;

    if(Parent != null)
    {
        posX += Parent->XPos;
        posY += Parent->YPos;
    }

	Value = Value <= Max ? Value : Max;
	Value = Value >= Min ? Value : Min;

	window->Draw(sf::Shape::Line(posX, posY + (Height / 2), posX + Width, posY + (Height / 2), Height, sf::Color(240, 240, 240)));
	window->Draw(sf::Shape::Line(posX, posY + (Height / 2), posX + (((float)Value / (float)Max) * (float)Width), posY + (Height / 2), Height, sf::Color(50, 100, 170)));

	window->Draw(sf::Shape::Line(posX, posY, posX + Width, posY, 2, sf::Color(200, 200, 200)));
	window->Draw(sf::Shape::Line(posX, posY, posX, posY + Height, 2, sf::Color(200, 200, 200)));

	window->Draw(sf::Shape::Line(posX, posY + Height, posX + Width, posY + Height, 2, sf::Color(255, 255, 255)));
	window->Draw(sf::Shape::Line(posX + Width, posY, posX + Width, posY + Height, 2, sf::Color(255, 255, 255)));
}
