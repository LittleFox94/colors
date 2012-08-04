#include "../include/gui/uc_checkbox.h"

UC_CheckBox::UC_CheckBox(string label, int x, int y)
{
	XPos = x;
	YPos = y;

	Height = 15;

	_caption = label;

	_img.LoadFromFile("data/img/checkbox.png");
	_img.SetSmooth(true);

	_sprite.SetImage(_img);
	_sprite.SetSubRect(sf::IntRect(0, 0, 15, 15));

	_label.SetFont(sf::Font::GetDefaultFont());
	_label.SetSize(12);
	_label.SetBlendMode(sf::Blend::Alpha);
	_label.SetColor(sf::Color(0, 0, 0));
	_label.SetText(_caption);

	Width = 15 + _label.GetRect().GetWidth() + 2;

	Checked = false;
}

UC_CheckBox::~UC_CheckBox()
{
}

void UC_CheckBox::Draw(sf::RenderTarget *window)
{
	_sprite.SetPosition(XPos, YPos);
	_label.SetPosition(XPos + 17, YPos);

	window->Draw(_sprite);
	window->Draw(_label);
}

void UC_CheckBox::OnHover(int, int, GUI*)
{
	if(Checked)
		_sprite.SetSubRect(sf::IntRect(0, 60, 15, 75));
	else
		_sprite.SetSubRect(sf::IntRect(0, 15, 15, 30));
}

void UC_CheckBox::OnUnhover(int, int, GUI*)
{
	if(Checked)
		_sprite.SetSubRect(sf::IntRect(0, 45, 15, 60));
	else
		_sprite.SetSubRect(sf::IntRect(0, 0, 15, 15));
}

void UC_CheckBox::OnClick(int, int, GUI*)
{
	if(Checked)
		_sprite.SetSubRect(sf::IntRect(0, 75, 15, 90));
	else
		_sprite.SetSubRect(sf::IntRect(0, 30, 15, 45));
}

void UC_CheckBox::OnUnclick(int, int, GUI*)
{
	Checked = !Checked;

	if(Checked)
		_sprite.SetSubRect(sf::IntRect(0, 45, 15, 60));
	else
		_sprite.SetSubRect(sf::IntRect(0, 0, 15, 15));
}
