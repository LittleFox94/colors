#include "../include/gui/uc_window.h"
#include "../include/gui/gui.h"

UC_Window::UC_Window()
{
	XPos = 10;
	YPos = 10;

	Width = 600;
	Height = 500;

	Offset = 20;

	_gui = new GUI(this);
}

UC_Window::~UC_Window()
{
}

GUI *UC_Window::Gui()
{
    return _gui;
}

void UC_Window::Draw(sf::RenderTarget *SF_Window)
{
	SF_Window->Draw(sf::Shape::Line(XPos, YPos + 10, XPos + Width, YPos + 10, 20, sf::Color(0, 112, 201, 127)));

	SF_Window->Draw(sf::Shape::Line(XPos, YPos + 10 + (Height / 2), XPos + Width, YPos + 10 + (Height / 2), Height - 20, sf::Color(220, 220, 220, 240)));

	SF_Window->Draw(sf::Shape::Line(XPos, YPos, XPos, YPos + Height, 2, sf::Color(240, 240, 240)));
	SF_Window->Draw(sf::Shape::Line(XPos, YPos, XPos + Width, YPos, 2, sf::Color(240, 240, 240)));

	SF_Window->Draw(sf::Shape::Line(XPos + Width, YPos, XPos + Width, YPos + Height, 2, sf::Color(180, 180, 180)));
	SF_Window->Draw(sf::Shape::Line(XPos + Width, YPos + Height, XPos, YPos + Height, 2, sf::Color(180, 180, 180)));

	_gui->DrawItems(SF_Window);

	sf::String title;
	title.SetColor(sf::Color(255, 255, 255));
	title.SetFont(sf::Font::GetDefaultFont());
	title.SetText(Title);
	title.SetPosition(XPos + 5, YPos + 2);
	title.SetSize(12);
	title.SetBlendMode(sf::Blend::Add);
	SF_Window->Draw(title);
}

void UC_Window::OnHover(int posX, int posY, GUI *gui)
{
	_gui->HoverAtPos(posX - XPos, posY - YPos);
}

bool UC_Window::IsMovable()
{
	return true;
}

void UC_Window::OnClick(int posX, int posY, GUI *gui)
{
	_gui->ClickAtPos(posX - XPos, posY - YPos);
}

void UC_Window::OnUnclick(int posX, int posY, GUI *gui)
{
	_gui->UnclickAtPos(posX - XPos, posY - YPos);
}

void UC_Window::OnKeyPressed(char c)
{
    if(_gui->FocusedItem != null)
        _gui->FocusedItem->control->OnKeyPressed(c);
}
