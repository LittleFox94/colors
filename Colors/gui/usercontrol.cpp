#include "../include/gui/usercontrol.h"

UserControl::UserControl()
{
}

UserControl::~UserControl()
{
	Dispose();
}

void UserControl::Draw(sf::RenderTarget *window) { }
void UserControl::OnHover(int, int, GUI*) { }
void UserControl::OnUnhover(int, int, GUI*) { }
void UserControl::OnClick(int, int, GUI*) { }
void UserControl::OnUnclick(int, int, GUI*) { }
bool UserControl::IsMovable() {
	return false;
}
void UserControl::Dispose() { }
void UserControl::OnKeyPressed(char) { }
