#include "../include/gui/uc_combobox.h"

UC_ComboBox::UC_ComboBox(int x, int y, int w)
{
    XPos = x;
    YPos = y;
    Width = w;
    Height = 20;

	_buttonImg = new sf::Image();
    _buttonImg->LoadFromFile("res/img/gui/combobox.png");

    _buttonSprite = new sf::Sprite();
    _buttonSprite->SetImage(*_buttonImg);
    _buttonSprite->SetSubRect(sf::IntRect(0, 0, _buttonImg->GetWidth(), _buttonImg->GetHeight() / 3));

    _isOpened = false;

    _firstItem = null;
    _lastItem = null;
    _currentItem = null;
}

UC_ComboBox::~UC_ComboBox()
{
	delete _buttonSprite;
	delete _buttonImg;
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
    int posX = XPos;
    int posY = YPos;

    if(Parent != null)
    {
        posX += Parent->XPos;
        posY += Parent->YPos + Parent->Offset;
    }

    window->Draw(sf::Shape::Line(posX, posY + 10, posX + Width, posY + 10, 20, sf::Color(240, 240, 240)));

    _buttonSprite->SetPosition(posX + Width - 15, posY);
    window->Draw(*_buttonSprite);

    if(_currentItem != null)
    {
        sf::String mainCaption;
        mainCaption.SetText(_currentItem->caption);
        mainCaption.SetSize(12);
        mainCaption.SetColor(sf::Color(0, 0, 0));
        mainCaption.SetPosition(posX + 2, posY + 2);
        mainCaption.SetFont(sf::Font::GetDefaultFont());
        window->Draw(mainCaption);
    }

    if(_isOpened)
    {
        int count = _lastItem->id + 1;

        window->Draw(sf::Shape::Line(posX, posY + 20 + ((count * 20) / 2), posX + Width, posY + 20 + ((count * 20) / 2), count * 20, sf::Color(240, 240, 240), 1, sf::Color(0, 0, 0)));

        if(_hoveredItem < count)
            window->Draw(sf::Shape::Line(posX, posY + 30 + ((_hoveredItem) * 20), posX + Width, posY + 30 + ((_hoveredItem) * 20), 20, sf::Color(70, 100, 220)));

        sf::String captions[count];

        struct COMBOBOX_ITEM *current = _firstItem;
        for(int i = 0; i < count; i++)
        {
            if(current == null)
                break;

            captions[i].SetText(current->caption);
            captions[i].SetSize(12);

            if(i == _hoveredItem)
                captions[i].SetColor(sf::Color(240, 240, 240));
            else
                captions[i].SetColor(sf::Color(0, 0, 0));

            captions[i].SetPosition(posX + 2, posY + 22 + (i * 20));
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
    _buttonSprite->SetSubRect(sf::IntRect(0, _buttonImg->GetHeight() / 3, _buttonImg->GetWidth(), (_buttonImg->GetHeight() / 3) * 2));

    if(y - YPos - 20> 0)
    {
        _hoveredItem = (y - YPos - 20) / 20;
    }
}

void UC_ComboBox::OnUnhover(int, int, GUI*)
{
    _buttonSprite->SetSubRect(sf::IntRect(0, 0, _buttonImg->GetWidth(), _buttonImg->GetHeight() / 3));
}

void UC_ComboBox::OnClick(int x, int y, GUI*)
{
    _buttonSprite->SetSubRect(sf::IntRect(0, (_buttonImg->GetHeight() / 3) * 2, _buttonImg->GetWidth(), (_buttonImg->GetHeight() / 3) * 3));

    if(y - YPos - 20 > 0)
    {
        if(_hoveredItem == (y - YPos - 20) / 20)
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
    _buttonSprite->SetSubRect(sf::IntRect(0, _buttonImg->GetHeight() / 3, _buttonImg->GetWidth(), (_buttonImg->GetHeight() / 3) * 2));
    _isOpened = !_isOpened;

    if(_isOpened)
    {
        Height = 20 + (_lastItem->id + 1) * 20;
        Width += 50;
    }

    else
    {
        Height = 20;
        Width -= 50;
    }
}
