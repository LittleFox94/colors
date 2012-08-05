#include "../include/gui/gui.h"

GUI::GUI(UserControl *parent)
{
    _firstGuiItem = null;
	_lastGuiItem = null;
	FocusedItem = null;
	hasChanged = true;
	IsMoving = false;

    _parentControl = parent;
}

GUI::~GUI()
{
	GUI_ITEM *next =null;
	GUI_ITEM *current = _firstGuiItem;
	while(current != null)
	{
		next = current->next;
		current->control->~UserControl();
		free(current);
		current = next;
	}

	printf("[ GUI ] GUI Object deleted!\n");
}

void GUI::DrawItems(sf::RenderTarget *window)
{
	struct GUI_ITEM *current = _firstGuiItem;

	while(current != null)
	{
	    if(current != FocusedItem)
            current->control->Draw(window);

		current = current->next;
	}

	if(FocusedItem != null)
        FocusedItem->control->Draw(window);
}

void GUI::AddItem(UserControl *control)
{
	struct GUI_ITEM *newItem = new GUI_ITEM();
	newItem->control = control;
	newItem->next = null;
	newItem->last = null;

	if(_lastGuiItem != null)
	{
		newItem->last = _lastGuiItem;
		_lastGuiItem->next = newItem;

		_lastGuiItem = newItem;
	}
	else
	{
		_lastGuiItem = newItem;
		_firstGuiItem = newItem;
	}

	control->Parent = _parentControl;

    FocusedItem = null;

	printf(string("[ GUI ] New UserControl added!\n").c_str());
}

void GUI::RemoveItem(UserControl *control)
{
    struct GUI_ITEM *current = _firstGuiItem;

    while(current->control != control && current != null)
    {
        current = current->next;
    }

    if(current == null)
    {
        return;
    }

    if(current == _firstGuiItem)
    {
        _firstGuiItem = current->next;
        _firstGuiItem->last = null;
    }

    if(current == _lastGuiItem)
    {
        _lastGuiItem = current->last;
        _lastGuiItem->next = null;
    }

    if(current == FocusedItem)
    {
        FocusedItem = null;
    }

    if(current->last != null)
    {
        current->last->next = current->next;
    }

    if(current->next != null)
    {
        current->next->last = current->last;
    }

    delete current;
}

void GUI::HoverAtPos(int posX, int posY)
{
	if(IsMoving)
		return;
	struct GUI_ITEM *current = _lastGuiItem;

	bool found = false;

	while(current != null)
	{
		int x, y, w, h;
		x = current->control->XPos;
		y = current->control->YPos;
		w = current->control->Width;
		h = current->control->Height;

		if(posX > x && posX < x + w && posY > y && posY < y + h && !found)
		{
			current->control->OnHover(posX, posY, this);
			found = true;
		}

		else
			current->control->OnUnhover(posX, posY, this);

		current = current->last;
	}
}

void GUI::ClickAtPos(int posX, int posY)
{
	if(IsMoving)
		return;
	struct GUI_ITEM *current = _lastGuiItem;

	bool found = false;

	while(current != null)
	{
		int x, y, w, h;
		x = current->control->XPos;
		y = current->control->YPos;
		w = current->control->Width;
		h = current->control->Height;

		if(posX > x && posX < x + w && posY > y && posY < y + h && !found)
		{
			current->control->OnClick(posX, posY, this);
			found = true;
			FocusedItem = current;
			current->control->hasFocus = true;
		}
		else
		{
			current->control->OnUnhover(posX, posY, this);
			current->control->hasFocus = false;
		}

		current = current->last;
	}
}

void GUI::UnclickAtPos(int posX, int posY)
{
	if(IsMoving)
		return;

	struct GUI_ITEM *current = _lastGuiItem;
	bool found = false;

	while(current != null)
	{
		int x, y, w, h;
		x = current->control->XPos;
		y = current->control->YPos;
		w = current->control->Width;
		h = current->control->Height;

		if(posX > x && posX < x + w && posY > y && posY < y + h && !found)
		{
			current->control->OnUnclick(posX, posY, this);
			found = true;
		}
		else
			current->control->OnUnhover(posX, posY, this);

		current = current->last;
	}
}

bool GUI::MoveControlAt(int posX, int posY, int oldX, int oldY)
{
	struct GUI_ITEM *current = _firstGuiItem;

	while(current != null)
	{
		int x, y, w, h;
		x = current->control->XPos;
		y = current->control->YPos;
		w = current->control->Width;
		h = current->control->Height;

		if(posX > x && posX < x + w && posY > y && posY < y + h && current->control->IsMovable())
		{
			IsMoving = true;
			current->control->XPos -= oldX - posX;
			current->control->YPos -= oldY - posY;
			return true;
		}

		current = current->next;
	}
	return false;
}
