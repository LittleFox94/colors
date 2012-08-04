#include "../include/gui/uc_button.h"
#include "../include/gui/gui.h"

UC_Button::UC_Button()
{
	_buttonImg.LoadFromFile("data/img/button_klein.png");
	_buttonSprite.SetImage(_buttonImg);
	_buttonSprite.SetPosition(XPos, YPos);
	_buttonSprite.SetSubRect(sf::IntRect(0, 0, _buttonImg.GetWidth(), _buttonImg.GetHeight() / 3));
	callback = null;

	Width = _buttonImg.GetWidth();
	Height = _buttonImg.GetHeight() / 3;
}

UC_Button::UC_Button(string imgFileName, int posX, int posY, void *cb)
{
	_buttonImg.LoadFromFile(imgFileName);
	_buttonSprite.SetImage(_buttonImg);
	_buttonSprite.SetPosition(posX, posY);
	_buttonSprite.SetSubRect(sf::IntRect(0, 0, _buttonImg.GetWidth(), _buttonImg.GetHeight() / 3));

	XPos = posX;
	YPos = posY;
	Width = _buttonImg.GetWidth();
	Height = _buttonImg.GetHeight() / 3;

	callback = cb;
}

UC_Button::UC_Button(string imgFileName, string caption, int posX, int posY, void *cb)
{
	_buttonImg.LoadFromFile(imgFileName);
	_buttonSprite.SetImage(_buttonImg);

	_buttonSprite.SetPosition(posX, posY);

	_buttonSprite.SetSubRect(sf::IntRect(0, 0, _buttonImg.GetWidth(), _buttonImg.GetHeight() / 3));

	XPos = posX;
	YPos = posY;
	Width = _buttonImg.GetWidth();
	Height = _buttonImg.GetHeight() / 3;

	callback = cb;

	_label.SetPosition(posX + 10, posY + 5);
	_label.SetSize(12);
	_label.SetText(caption);
	_label.SetColor(sf::Color(255, 255, 255));
	_label.SetFont(sf::Font::GetDefaultFont());
	_label.SetBlendMode(sf::Blend::Add);
}

UC_Button::UC_Button(string imgFileName, int posX, int posY, void *cb, void *param)
{
	_buttonImg.LoadFromFile(imgFileName);
	_buttonSprite.SetImage(_buttonImg);
	_buttonSprite.SetPosition(posX, posY);
	_buttonSprite.SetSubRect(sf::IntRect(0, 0, _buttonImg.GetWidth(), _buttonImg.GetHeight() / 3));

	XPos = posX;
	YPos = posY;
	Width = _buttonImg.GetWidth();
	Height = _buttonImg.GetHeight() / 3;

	callback = cb;
	callbackParam = param;
}

UC_Button::UC_Button(string imgFileName, string caption, int posX, int posY, void *cb, void *param)
{
	_buttonImg.LoadFromFile(imgFileName);
	_buttonSprite.SetImage(_buttonImg);

	_buttonSprite.SetPosition(posX, posY);

	_buttonSprite.SetSubRect(sf::IntRect(0, 0, _buttonImg.GetWidth(), _buttonImg.GetHeight() / 3));

	XPos = posX;
	YPos = posY;
	Width = _buttonImg.GetWidth();
	Height = _buttonImg.GetHeight() / 3;

	callback = cb;
	callbackParam = param;

	_label.SetPosition(posX + 10, posY + 5);
	_label.SetSize(12);
	_label.SetText(caption);
	_label.SetColor(sf::Color(255, 255, 255));
	_label.SetFont(sf::Font::GetDefaultFont());
	_label.SetBlendMode(sf::Blend::Add);
}

UC_Button::~UC_Button()
{
}

void UC_Button::Dispose()
{
	_buttonSprite.~Drawable();
	_buttonImg.~Image();
}

void UC_Button::Draw(sf::RenderTarget *window)
{
	_buttonSprite.SetPosition(XPos, YPos);
	_label.SetPosition(XPos + 10, YPos + 5);
	window->Draw(_buttonSprite);
	window->Draw(_label);
}

void UC_Button::OnHover(int, int, GUI*)
{
	_buttonSprite.SetSubRect(sf::IntRect(0, _buttonImg.GetHeight() / 3, _buttonImg.GetWidth(), (_buttonImg.GetHeight() / 3) * 2));
}

void UC_Button::OnUnhover(int, int, GUI*)
{
	_buttonSprite.SetSubRect(sf::IntRect(0, 0, _buttonImg.GetWidth(), _buttonImg.GetHeight() / 3));
}

void UC_Button::OnClick(int, int, GUI*)
{
	_buttonSprite.SetSubRect(sf::IntRect(0, (_buttonImg.GetHeight() / 3) * 2, _buttonImg.GetWidth(), (_buttonImg.GetHeight() / 3) * 3));
}

void UC_Button::OnUnclick(int, int, GUI* gui)
{
	_buttonSprite.SetSubRect(sf::IntRect(0, _buttonImg.GetHeight() / 3, _buttonImg.GetWidth(), (_buttonImg.GetHeight() / 3) * 2));
	if(callback != null)
	{
		if(callbackParam != null)
		{
			void (*cb)(void *) = (void(*)(void *))callback;
			cb(callbackParam);
		}
		else
		{
			void (*cb)() = (void (*)())callback;
			cb();
		}
	}

	if(gui != null && callback != null)
		gui->hasChanged = true;
}
