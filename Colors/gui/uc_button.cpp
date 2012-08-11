#include "../include/gui/uc_button.h"
#include "../include/gui/gui.h"

UC_Button::UC_Button()
{
	_buttonImg = new sf::Image();
	_buttonImg->LoadFromFile("data/img/button_klein.png");

	_buttonSprite = new sf::Sprite();
	_buttonSprite->SetImage(*_buttonImg);
	_buttonSprite->SetPosition(XPos, YPos);
	_buttonSprite->SetSubRect(sf::IntRect(0, 0, _buttonImg->GetWidth(), _buttonImg->GetHeight() / 3));
	callback = null;

	Width = _buttonImg->GetWidth();
	Height = _buttonImg->GetHeight() / 3;
}

UC_Button::UC_Button(string imgFileName, int posX, int posY, void *cb)
{
	_buttonImg = new sf::Image();
	_buttonImg->LoadFromFile(imgFileName);

	_buttonSprite = new sf::Sprite();
	_buttonSprite->SetImage(*_buttonImg);
	_buttonSprite->SetPosition(XPos, YPos);
	_buttonSprite->SetSubRect(sf::IntRect(0, 0, _buttonImg->GetWidth(), _buttonImg->GetHeight() / 3));

	XPos = posX;
	YPos = posY;
	Width = _buttonImg->GetWidth();
	Height = _buttonImg->GetHeight() / 3;

	callback = cb;
}

UC_Button::UC_Button(string imgFileName, string caption, int posX, int posY, void *cb)
{
	_buttonImg = new sf::Image();
	_buttonImg->LoadFromFile(imgFileName);

	_buttonSprite = new sf::Sprite();
	_buttonSprite->SetImage(*_buttonImg);
	_buttonSprite->SetPosition(XPos, YPos);
	_buttonSprite->SetSubRect(sf::IntRect(0, 0, _buttonImg->GetWidth(), _buttonImg->GetHeight() / 3));

	XPos = posX;
	YPos = posY;
	Width = _buttonImg->GetWidth();
	Height = _buttonImg->GetHeight() / 3;

	callback = cb;

    _label = new UC_Label(caption, sf::Color(255, 255, 255), Height / 2, XPos + 10, YPos + (Height / 6));
}

UC_Button::UC_Button(string imgFileName, int posX, int posY, void *cb, void *param)
{
	_buttonImg = new sf::Image();
	_buttonImg->LoadFromFile(imgFileName);

	_buttonSprite = new sf::Sprite();
	_buttonSprite->SetImage(*_buttonImg);
	_buttonSprite->SetPosition(XPos, YPos);
	_buttonSprite->SetSubRect(sf::IntRect(0, 0, _buttonImg->GetWidth(), _buttonImg->GetHeight() / 3));

	XPos = posX;
	YPos = posY;
	Width = _buttonImg->GetWidth();
	Height = _buttonImg->GetHeight() / 3;

	callback = cb;
	callbackParam = param;
}

UC_Button::UC_Button(string imgFileName, string caption, int posX, int posY, void *cb, void *param)
{
	_buttonImg = new sf::Image();
	_buttonImg->LoadFromFile(imgFileName);

	_buttonSprite = new sf::Sprite();
	_buttonSprite->SetImage(*_buttonImg);
	_buttonSprite->SetPosition(XPos, YPos);
	_buttonSprite->SetSubRect(sf::IntRect(0, 0, _buttonImg->GetWidth(), _buttonImg->GetHeight() / 3));

	XPos = posX;
	YPos = posY;
	Width = _buttonImg->GetWidth();
	Height = _buttonImg->GetHeight() / 3;

	callback = cb;
	callbackParam = param;

	_label = new UC_Label(caption, sf::Color(255, 255, 255), Height / 2, XPos + 10, YPos + (Height / 6));
}

UC_Button::~UC_Button()
{
	delete _buttonSprite;
	delete _buttonImg;
	delete _label;
}

void UC_Button::Draw(sf::RenderTarget *window)
{
    int posX = XPos;
    int posY = YPos;

    if(Parent != null)
    {
        posX += Parent->XPos;
        posY += Parent->YPos + Parent->Offset;
    }

	_buttonSprite->SetPosition(posX, posY);
	window->Draw(*_buttonSprite);

    _label->Parent = Parent;
	_label->Draw(window);
}

void UC_Button::OnHover(int, int, GUI*)
{
	_buttonSprite->SetSubRect(sf::IntRect(0, _buttonImg->GetHeight() / 3, _buttonImg->GetWidth(), (_buttonImg->GetHeight() / 3) * 2));
}

void UC_Button::OnUnhover(int, int, GUI*)
{
	_buttonSprite->SetSubRect(sf::IntRect(0, 0, _buttonImg->GetWidth(), _buttonImg->GetHeight() / 3));
}

void UC_Button::OnClick(int, int, GUI*)
{
	_buttonSprite->SetSubRect(sf::IntRect(0, (_buttonImg->GetHeight() / 3) * 2, _buttonImg->GetWidth(), (_buttonImg->GetHeight() / 3) * 3));
}

void UC_Button::OnUnclick(int, int, GUI* gui)
{
	_buttonSprite->SetSubRect(sf::IntRect(0, _buttonImg->GetHeight() / 3, _buttonImg->GetWidth(), (_buttonImg->GetHeight() / 3) * 2));
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
