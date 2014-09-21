#include "../../include/gui/usercontrol.h"

UserControl::UserControl()
{
    Parent = null;
}

UserControl::~UserControl()
{
}

void UserControl::Draw(sf::RenderTarget *window) { }
void UserControl::OnHover(int, int, GUI*) { }
void UserControl::OnUnhover(int, int, GUI*) { }
void UserControl::OnClick(int, int, GUI*) { }
void UserControl::OnUnclick(int, int, GUI*) { }
bool UserControl::IsMovable() {
	return false;
}
void UserControl::OnKeyPressed(char) { }
