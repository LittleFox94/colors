#include "../../include/gui/uc_window.h"
#include "../../include/gui/gui.h"

UC_Window::UC_Window()
{
	XPos = 10;
	YPos = 10;

	Width = 600;
	Height = 500;

	Offset = 20;

	_gui = new GUI(this);

    _titleBar = new sf::RectangleShape();
    _titleBar->setPosition(XPos, YPos);
    _titleBar->setSize(sf::Vector2f(Width, 18));
    _titleBar->setFillColor(sf::Color(0, 112, 201, 127));

    _contentArea = new sf::RectangleShape();
    _contentArea->setPosition(XPos, YPos);
    _contentArea->setSize(sf::Vector2f(Width, Height - 18));
    _contentArea->setFillColor(sf::Color(220, 220, 220, 240));
    _contentArea->setOutlineThickness(2);
    _contentArea->setOutlineColor(sf::Color(0, 112, 201, 127));
}

UC_Window::~UC_Window()
{
}

GUI *UC_Window::Gui()
{
    return _gui;
}

void UC_Window::Draw(sf::RenderTarget *window)
{
    _titleBar->setPosition(XPos, YPos);
    _titleBar->setSize(sf::Vector2f(Width, 18));
    _contentArea->setPosition(XPos, YPos+20);
    _contentArea->setSize(sf::Vector2f(Width, Height - 18));

    window->draw(*_titleBar);
    window->draw(*_contentArea);

	_gui->DrawItems(window);

	sf::Text title;
	title.setFillColor(sf::Color(255, 255, 255));
	title.setString(Title);
	title.setPosition(XPos + 5, YPos + 2);
	title.setCharacterSize(12);
	window->draw(title);
}

void UC_Window::OnHover(int posX, int posY, GUI *gui)
{
	_gui->HoverAtPos(posX - XPos, posY - YPos - Offset);
}

bool UC_Window::IsMovable()
{
	return true;
}

void UC_Window::OnClick(int posX, int posY, GUI *gui)
{
	_gui->ClickAtPos(posX - XPos, posY - YPos - Offset);
}

void UC_Window::OnUnclick(int posX, int posY, GUI *gui)
{
	_gui->UnclickAtPos(posX - XPos, posY - YPos - Offset);
}

void UC_Window::OnKeyPressed(char c)
{
    if(_gui->FocusedItem != null)
        _gui->FocusedItem->control->OnKeyPressed(c);
}
