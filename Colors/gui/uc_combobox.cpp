#include "../include/gui/uc_combobox.h"

UC_ComboBox::UC_ComboBox(int x, int y, int w)
{
	XPos = x;
	YPos = y;
	Width = w;
	Height = 20;

	_buttonImg.LoadFromFile("data/img/combobox.png");
	_buttonSprite.SetImage(_buttonImg);
	_buttonSprite.SetSubRect(sf::IntRect(0, 0, _buttonImg.GetWidth(), _buttonImg.GetHeight() / 3));

	_isOpened = false;

	_firstItem = null;
	_lastItem = null;
	_currentItem = null;
}

UC_ComboBox::~UC_ComboBox()
{
}

void UC_ComboBox::Dispose()
{
}

void UC_ComboBox::SetCurrentIndex(int index)
{
	CurrentIndex = index;
	struct COMBOBOX_ITEM *current = _firstItem;
	while(current != null)
	{
		if(current->id == CurrentIndex)
		{
			_currentItem = current;
			break;
		}
		else
			current = current->next;
	}
}

void UC_ComboBox::Draw(sf::RenderTarget *window)
{
	window->Draw(sf::Shape::Line(XPos, YPos + 10, XPos + Width, YPos + 10, 20, sf::Color(240, 240, 240)));

	_buttonSprite.SetPosition(XPos + Width - 15, YPos);
	window->Draw(_buttonSprite);

	if(_currentItem != null)
	{
		sf::String mainCaption;
		mainCaption.SetText(_currentItem->caption);
		mainCaption.SetSize(12);
		mainCaption.SetColor(sf::Color(0, 0, 0));
		mainCaption.SetPosition(XPos + 2, YPos + 2);
		mainCaption.SetFont(sf::Font::GetDefaultFont());
		window->Draw(mainCaption);
	}

	if(_isOpened)
	{
		window->Draw(sf::Shape::Line(XPos, YPos + 70, XPos + Width, YPos + 70, 100, sf::Color(240, 240, 240), 1, sf::Color(0, 0, 0)));

		window->Draw(sf::Shape::Line(XPos, YPos + 30 + ((_hoveredItem) * 20), XPos + Width, YPos + 30 + ((_hoveredItem) * 20), 20, sf::Color(70, 100, 220)));

		sf::String captions[5];

		struct COMBOBOX_ITEM *current = _firstItem;
		for(int i = 0; i < 5; i++)
		{
			if(current == null)
				break;

			captions[i].SetText(current->caption);
			captions[i].SetSize(12);

			if(i == _hoveredItem)
				captions[i].SetColor(sf::Color(240, 240, 240));
			else
				captions[i].SetColor(sf::Color(0, 0, 0));

			captions[i].SetPosition(XPos + 2, YPos + 22 + (i * 20));
			captions[i].SetFont(sf::Font::GetDefaultFont());
			window->Draw(captions[i]);

			current = current->next;
		}
	}
}

void UC_ComboBox::AddItem(string caption)
{
	struct COMBOBOX_ITEM *newItem = new COMBOBOX_ITEM();
	newItem->caption = caption;

	if(_firstItem == null)
	{
		newItem->id = 0;
		_lastItem = newItem;
		_firstItem = newItem;
	}
	else
	{
		newItem->id = _lastItem->id + 1;

		newItem->last = _lastItem;
		_lastItem->next = newItem;
		_lastItem = newItem;
	}
}

void UC_ComboBox::OnHover(int x, int y, GUI*)
{
	_buttonSprite.SetSubRect(sf::IntRect(0, _buttonImg.GetHeight() / 3, _buttonImg.GetWidth(), (_buttonImg.GetHeight() / 3) * 2));

	if(y - (YPos + Parent->YPos + Parent->Offset + 20) > 0)
	{
		_hoveredItem = (y - (YPos + Parent->YPos + Parent->Offset + 20)) / 20;
	}
}

void UC_ComboBox::OnUnhover(int, int, GUI*)
{
	_buttonSprite.SetSubRect(sf::IntRect(0, 0, _buttonImg.GetWidth(), _buttonImg.GetHeight() / 3));
}

void UC_ComboBox::OnClick(int x, int y, GUI*)
{
	_buttonSprite.SetSubRect(sf::IntRect(0, (_buttonImg.GetHeight() / 3) * 2, _buttonImg.GetWidth(), (_buttonImg.GetHeight() / 3) * 3));

	if(y - (YPos + Parent->YPos + Parent->Offset + 20) > 0)
	{
		if(_hoveredItem == (y - (YPos + Parent->YPos + Parent->Offset + 20)) / 20)
		{
			CurrentIndex = _hoveredItem;

			struct COMBOBOX_ITEM *current = _firstItem;
			while(current != null)
			{
				if(current->id == CurrentIndex)
				{
					_currentItem = current;
					break;
				}
				else
					current = current->next;
			}
		}
	}
}

void UC_ComboBox::OnUnclick(int, int, GUI* gui)
{
	_buttonSprite.SetSubRect(sf::IntRect(0, _buttonImg.GetHeight() / 3, _buttonImg.GetWidth(), (_buttonImg.GetHeight() / 3) * 2));
	_isOpened = !_isOpened;

	if(_isOpened)
	{
		Height = 120;
		Width += 50;
	}

	else
	{
		Height = 20;
		Width -= 50;
	}
}
