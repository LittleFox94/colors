#include "../../include/gui/uc_combobox.h"

UC_ComboBox::UC_ComboBox(int x, int y, int w)
{
    XPos = x;
    YPos = y;
    Width = w;
    Height = 20;

	_font = new sf::Font();
	_font->loadFromFile("res/fonts/kaliberr.ttf");

	_buttonImg = new sf::Texture();
    _buttonImg->loadFromFile("res/img/gui/combobox.png");

    _buttonSprite = new sf::Sprite();
    _buttonSprite->setTexture(*_buttonImg);
    _buttonSprite->setTextureRect(sf::IntRect(0, 0, _buttonImg->getSize().x, _buttonImg->getSize().y / 3));

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

//    window->draw(sf::Shape::Line(posX, posY + 10, posX + Width, posY + 10, 20, sf::Color(240, 240, 240)));

    _buttonSprite->setPosition(posX + Width - 15, posY);
    window->draw(*_buttonSprite);

    if(_currentItem != null)
    {
        sf::Text mainCaption;
        mainCaption.setFont(*_font);
        mainCaption.setString(_currentItem->caption);
        mainCaption.setCharacterSize(12);
        mainCaption.setFillColor(sf::Color(0, 0, 0));
        mainCaption.setPosition(posX + 2, posY + 2);
        window->draw(mainCaption);
    }

    if(_isOpened)
    {
        int count = _lastItem->id + 1;

        sf::RectangleShape bg;
        bg.setSize(sf::Vector2f(Width, count * 20));
        bg.setPosition(posX, posY + 20);
        bg.setFillColor(sf::Color(240, 240, 240));
        bg.setOutlineThickness(1);
        bg.setOutlineColor(sf::Color(0, 0, 0));
        window->draw(bg);

        if(_hoveredItem < count) {
            sf::RectangleShape highlight;
            highlight.setSize(sf::Vector2f(Width, 20));
            highlight.setPosition(posX, posY + 20 + (_hoveredItem * 20));
            highlight.setFillColor(sf::Color(70, 100, 220));
            window->draw(highlight);
        }

        sf::Text captions[count];

        struct COMBOBOX_ITEM *current = _firstItem;
        for(int i = 0; i < count; i++)
        {
            if(current == null)
                break;

            captions[i].setFont(*_font);
            captions[i].setString(current->caption);
            captions[i].setCharacterSize(12);

            if(i == _hoveredItem)
                captions[i].setFillColor(sf::Color(240, 240, 240));
            else
                captions[i].setFillColor(sf::Color(0, 0, 0));

            captions[i].setPosition(posX + 2, posY + 22 + (i * 20));
            window->draw(captions[i]);

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
    _buttonSprite->setTextureRect(sf::IntRect(0, _buttonImg->getSize().y / 3, _buttonImg->getSize().x, _buttonImg->getSize().y / 3));

    if(y - YPos - 20> 0)
    {
        _hoveredItem = (y - YPos - 20) / 20;
    }
}

void UC_ComboBox::OnUnhover(int, int, GUI*)
{
    _buttonSprite->setTextureRect(sf::IntRect(0, 0, _buttonImg->getSize().x, _buttonImg->getSize().y / 3));
}

void UC_ComboBox::OnClick(int x, int y, GUI*)
{
    _buttonSprite->setTextureRect(sf::IntRect(0, (_buttonImg->getSize().y / 3) * 2, _buttonImg->getSize().x, _buttonImg->getSize().y / 3));

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
    _buttonSprite->setTextureRect(sf::IntRect(0, _buttonImg->getSize().y / 3, _buttonImg->getSize().x, _buttonImg->getSize().y / 3));
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
