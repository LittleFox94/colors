#include "../../include/gui/uc_lineedit.h"

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
    int posX = XPos;
    int posY = YPos;

    if(Parent != null)
    {
        posX += Parent->XPos;
        posY += Parent->YPos + Parent->Offset;
    }

	window->Draw(sf::Shape::Line(posX, posY + Height / 2, posX + Width, posY + Height / 2, Height, sf::Color(240, 240, 240)));

	window->Draw(sf::Shape::Line(posX, posY, posX + Width, posY, 2, sf::Color(200, 200, 200)));
	window->Draw(sf::Shape::Line(posX, posY, posX, posY + Height, 2, sf::Color(200, 200, 200)));

	window->Draw(sf::Shape::Line(posX, posY + Height, posX + Width, posY + Height, 2, sf::Color(255, 255, 255)));
	window->Draw(sf::Shape::Line(posX + Width, posY, posX + Width, posY + Height, 2, sf::Color(255, 255, 255)));

	unsigned int maxChars = ((Width / (Height - 4)) * 2) - 1;

	string temp;

	if(_content.length() > maxChars)
		temp = _content.substr(_content.length() - maxChars, maxChars);
	else
		temp = _content;

	sf::String text;
	text.SetText(temp);
	text.SetPosition(posX+ 2, posY);
	text.SetFont(sf::Font::GetDefaultFont());
	text.SetSize(Height - 4);
	text.SetColor(sf::Color(0, 0, 0));
	window->Draw(text);

	if(hasFocus)
	{
		aniState++;

		if(aniState < 60)
			window->Draw(sf::Shape::Line(posX + text.GetRect().GetWidth() + 4, posY + 2, posX + text.GetRect().GetWidth() + 4, posY + Height - 2, 1, sf::Color(0, 0, 0)));
		else if(aniState >= 120)
			aniState = 0;
	}
}
