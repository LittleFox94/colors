#ifndef USERCONTROL_H
#define USERCONTROL_H

#include <SFML/Graphics.hpp>
#include "../main.h"

class GUI;

class UserControl
{
	public:
		UserControl();
		~UserControl();

		int XPos, YPos, Width, Height, Offset;

		UserControl *Parent; // Nur lesen! Änderungen werden ignoriert, können aber Fehler verursachen!

		virtual void Draw(sf::RenderTarget *);
		virtual void OnHover(int, int, GUI*);
		virtual void OnUnhover(int, int, GUI*);
		virtual void OnClick(int, int, GUI*);
		virtual void OnUnclick(int, int, GUI*);
		virtual bool IsMovable();
		virtual void OnKeyPressed(char);

		bool hasFocus;
	protected:
	private:
};

#endif // USERCONTROL_H
