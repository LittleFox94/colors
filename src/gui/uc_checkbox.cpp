#include "../../include/gui/uc_checkbox.h"

UC_CheckBox::UC_CheckBox(string label, int x, int y)
{
	XPos = x;
	YPos = y;

	Height = 15;

	_caption = label;

	_img = new sf::Texture();
	_img->loadFromFile("res/img/gui/checkbox.png");
	_img->setSmooth(true);

	_sprite = new sf::Sprite();
	_sprite->setTexture(*_img);
	_sprite->setTextureRect(sf::IntRect(0, 0, 15, 15));


	_font = new sf::Font();
	_font->loadFromFile("res/fonts/kaliberr.ttf");

	_label = new sf::Text();
	_label->setFont(*_font);
	_label->setCharacterSize(12);
	_label->setFillColor(sf::Color(0, 0, 0));
	_label->setString(_caption);

	Width = 15 + _label->getLocalBounds().width + 2;

	Checked = false;
}

UC_CheckBox::~UC_CheckBox()
{
	delete _sprite;
	delete _img;
	delete _label;
}

void UC_CheckBox::Draw(sf::RenderTarget *window)
{
    int posX = XPos;
    int posY = YPos;

    if(Parent != null)
    {
        posX += Parent->XPos;
        posY += Parent->YPos + Parent->Offset;
    }

	_sprite->setPosition(posX, posY);
	_label->setPosition(posX + 17, posY);

	window->draw(*_sprite);
	window->draw(*_label);
}

void UC_CheckBox::OnHover(int, int, GUI*)
{
	if(Checked)
		_sprite->setTextureRect(sf::IntRect(0, 60, 15, 15));
	else
		_sprite->setTextureRect(sf::IntRect(0, 15, 15, 15));
}

void UC_CheckBox::OnUnhover(int, int, GUI*)
{
	if(Checked)
		_sprite->setTextureRect(sf::IntRect(0, 45, 15, 15));
	else
		_sprite->setTextureRect(sf::IntRect(0, 0, 15, 15));
}

void UC_CheckBox::OnClick(int, int, GUI*)
{
	if(Checked)
		_sprite->setTextureRect(sf::IntRect(0, 75, 15, 15));
	else
		_sprite->setTextureRect(sf::IntRect(0, 30, 15, 15));
}

void UC_CheckBox::OnUnclick(int, int, GUI*)
{
	Checked = !Checked;

	if(Checked)
		_sprite->setTextureRect(sf::IntRect(0, 45, 15, 15));
	else
		_sprite->setTextureRect(sf::IntRect(0, 0, 15, 15));
}
