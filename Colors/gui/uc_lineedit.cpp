#include "../include/gui/uc_lineedit.h"

UC_LineEdit::UC_LineEdit(int x, int y, int w, int h)
{
	XPos = x;
	YPos = y;
	Width = w;
	Height = h;

	aniState = 0;
	hasFocus = false;
}

UC_LineEdit::~UC_LineEdit()
{
	//dtor
}

void UC_LineEdit::OnKeyPressed(char c)
{
	if(_content.size() > 0 && c == 8) // backspace
	{
		_content.erase(_content.end() - 1);
	}
	else
		_content.push_back(c);
}

void UC_LineEdit::Draw(sf::RenderTarget *window)
{
	window->Draw(sf::Shape::Line(XPos, YPos + Height / 2, XPos + Width, YPos + Height / 2, Height, sf::Color(240, 240, 240)));

	window->Draw(sf::Shape::Line(XPos, YPos, XPos + Width, YPos, 2, sf::Color(200, 200, 200)));
	window->Draw(sf::Shape::Line(XPos, YPos, XPos, YPos + Height, 2, sf::Color(200, 200, 200)));

	window->Draw(sf::Shape::Line(XPos, YPos + Height, XPos + Width, YPos + Height, 2, sf::Color(255, 255, 255)));
	window->Draw(sf::Shape::Line(XPos + Width, YPos, XPos + Width, YPos + Height, 2, sf::Color(255, 255, 255)));

	int maxChars = ((Width / (Height - 4)) * 2) - 1;

	string temp;

	if(_content.length() > maxChars)
		temp = _content.substr(_content.length() - maxChars, maxChars);
	else
		temp = _content;

	sf::String text;
	text.SetText(temp);
	text.SetPosition(XPos+ 2, YPos);
	text.SetFont(sf::Font::GetDefaultFont());
	text.SetSize(Height - 4);
	text.SetColor(sf::Color(0, 0, 0));
	window->Draw(text);

	if(hasFocus)
	{
		aniState++;

		if(aniState < 60)
			window->Draw(sf::Shape::Line(XPos + text.GetRect().GetWidth() + 4, YPos + 2, XPos + text.GetRect().GetWidth() + 4, YPos + Height - 2, 1, sf::Color(0, 0, 0)));
		else if(aniState >= 120)
			aniState = 0;
	}
}
