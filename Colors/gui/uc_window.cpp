#include "../include/gui/uc_window.h"
#include "../include/gui/gui.h"

UC_Window::UC_Window()
{
	XPos = 10;
	YPos = 10;

	Width = 600;
	Height = 500;

	Offset = 20;

	_item = null;
}

UC_Window::~UC_Window()
{
}

void UC_Window::Dispose()
{
	UC_WINDOW_ITEM *current = _item;
	UC_WINDOW_ITEM *next = null;
	while(current != null)
	{
		current->control->~UserControl();
		next = current->next;
		free(current);
		current = next;
	}
}

void UC_Window::Draw(sf::RenderTarget *SF_Window)
{
	SF_Window->Draw(sf::Shape::Line(XPos, YPos + 10, XPos + Width, YPos + 10, 20, sf::Color(0, 112, 201, 127)));

	SF_Window->Draw(sf::Shape::Line(XPos, YPos + 10 + (Height / 2), XPos + Width, YPos + 10 + (Height / 2), Height - 20, sf::Color(220, 220, 220, 240)));

	SF_Window->Draw(sf::Shape::Line(XPos, YPos, XPos, YPos + Height, 2, sf::Color(240, 240, 240)));
	SF_Window->Draw(sf::Shape::Line(XPos, YPos, XPos + Width, YPos, 2, sf::Color(240, 240, 240)));

	SF_Window->Draw(sf::Shape::Line(XPos + Width, YPos, XPos + Width, YPos + Height, 2, sf::Color(180, 180, 180)));
	SF_Window->Draw(sf::Shape::Line(XPos + Width, YPos + Height, XPos, YPos + Height, 2, sf::Color(180, 180, 180)));

	struct UC_WINDOW_ITEM *current = _item;
	while(current != null)
	{
		current->control->XPos += XPos;
		current->control->YPos += YPos + 20;
		current->control->Draw(SF_Window);
		current->control->XPos -= XPos;
		current->control->YPos -= YPos + 20;
		current = current->next;
	}

	sf::String title;
	title.SetColor(sf::Color(255, 255, 255));
	title.SetFont(sf::Font::GetDefaultFont());
	title.SetText(Title);
	title.SetPosition(XPos + 5, YPos + 2);
	title.SetSize(12);
	title.SetBlendMode(sf::Blend::Add);
	SF_Window->Draw(title);
}

void UC_Window::AddItem(UserControl *control)
{
	struct UC_WINDOW_ITEM newItem;
	newItem.control = control;
	newItem.next = _item;

	_item = (struct UC_WINDOW_ITEM*)malloc(sizeof(newItem));
	*_item = newItem;

	control->Parent = this;

	printf(string("[ UC_WINDOW ] New Child-UserControl added!\n").c_str());
}

void UC_Window::OnHover(int posX, int posY, GUI *gui)
{
	struct UC_WINDOW_ITEM *current = _item;
	struct UC_WINDOW_ITEM *found = null;

	while(current != null)
	{
		int x, y, w, h;
		x = current->control->XPos + XPos;
		y = current->control->YPos + YPos + 20;
		w = current->control->Width;
		h = current->control->Height;

		if(posX > x && posX < x + w && posY > y && posY < y + h)
		{
			current->control->OnHover(posX, posY, gui);

			if(found != null)
				found->control->OnUnhover(posX, posY, gui);
			found = current;

			_itemFound = true;
		}

		else
			current->control->OnUnhover(posX, posY, gui);

		current = current->next;
		_itemFound = false;
	}
}

bool UC_Window::IsMovable()
{

	return !_itemFound;
}

void UC_Window::OnClick(int posX, int posY, GUI *gui)
{
	struct UC_WINDOW_ITEM *current = _item;

	while(current != null)
	{
		int x, y, w, h;
		x = current->control->XPos + XPos;
		y = current->control->YPos + YPos + 20;
		w = current->control->Width;
		h = current->control->Height;

		if(posX > x && posX < x + w && posY > y && posY < y + h)
		{
			current->control->OnClick(posX, posY, gui);
			_itemFound = true;
			_focusedItem = current;
			current->control->hasFocus = true;
			return;
		}
		else
		{
			current->control->hasFocus = false;
		}
		_itemFound = false;
		current = current->next;
	}
}

void UC_Window::OnUnclick(int posX, int posY, GUI *gui)
{
	struct UC_WINDOW_ITEM *current = _item;

	while(current != null)
	{
		int x, y, w, h;
		x = current->control->XPos + XPos;
		y = current->control->YPos + YPos + 20;
		w = current->control->Width;
		h = current->control->Height;

		if(posX > x && posX < x + w && posY > y && posY < y + h)
		{
			current->control->OnUnclick(posX, posY, gui);
			_itemFound = true;
			return;
		}
		_itemFound = false;
		current = current->next;
	}
}

void UC_Window::OnKeyPressed(char c)
{
	if(_focusedItem != null)
		_focusedItem->control->OnKeyPressed(c);
}
