#include "../include/gui/uc_progressbar.h"

UC_ProgressBar::UC_ProgressBar(int min, int max, int x, int y, int w, int h)
{
	XPos = x;
	YPos = y;
	Width = w;
	Height = h;
	min = min;
	max = max;

	_aniImg.LoadFromFile("data/img/progress.png");
	_aniSprite.SetImage(_aniImg);
	_aniState = -_aniImg.GetWidth();
}

UC_ProgressBar::~UC_ProgressBar()
{
	//dtor
}

void UC_ProgressBar::Draw(sf::RenderTarget *window)
{
	Value = Value <= Max ? Value : Max;
	Value = Value >= Min ? Value : Min;

	window->Draw(sf::Shape::Line(XPos, YPos + (Height / 2), XPos + Width, YPos + (Height / 2), Height, sf::Color(240, 240, 240)));
	window->Draw(sf::Shape::Line(XPos, YPos + (Height / 2), XPos + (((float)Value / (float)Max) * (float)Width), YPos + (Height / 2), Height, sf::Color(50, 100, 170)));

	_aniState++;


	_aniSprite.SetSubRect(sf::IntRect(1, 1, _aniImg.GetHeight(), Height));

	if(_aniState + XPos < _aniImg.GetWidth())
	{
		_aniSprite.SetSubRect(sf::IntRect(_aniImg.GetWidth() - _aniState, 0, _aniImg.GetWidth(), Height));
		_aniSprite.SetCenter(_aniState, 0);
	}
	else if(_aniState >= (unsigned)(Value * Width / Max))
	{
		_aniSprite.SetSubRect(sf::IntRect(1, 1, _aniImg.GetWidth() + ((Value * Width / Max) - _aniState - XPos), Height));

		if(_aniImg.GetWidth() + ((Value * Width / Max) - _aniState - XPos) <= 0)
			_aniState = -_aniImg.GetWidth();
	}
	_aniSprite.SetPosition(XPos + _aniState, YPos);

	window->Draw(_aniSprite);

	window->Draw(sf::Shape::Line(XPos, YPos, XPos + Width, YPos, 2, sf::Color(200, 200, 200)));
	window->Draw(sf::Shape::Line(XPos, YPos, XPos, YPos + Height, 2, sf::Color(200, 200, 200)));

	window->Draw(sf::Shape::Line(XPos, YPos + Height, XPos + Width, YPos + Height, 2, sf::Color(255, 255, 255)));
	window->Draw(sf::Shape::Line(XPos + Width, YPos, XPos + Width, YPos + Height, 2, sf::Color(255, 255, 255)));
}
