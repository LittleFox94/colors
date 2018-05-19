#ifndef UC_WINDOW_H
#define UC_WINDOW_H

#include "gui.h"

class UC_Window : public UserControl
{
	public:
		UC_Window();
		virtual ~UC_Window();

		void Draw(sf::RenderTarget *);
		void OnHover(int, int, GUI*);
		void OnClick(int, int, GUI*);
		void OnUnclick(int, int, GUI*);
		bool IsMovable();
		void OnKeyPressed(char);

		GUI *Gui();

		string Title;
	protected:
	private:
		GUI *_gui;

        sf::RectangleShape *_titleBar;
        sf::RectangleShape *_contentArea;
};

#endif // UC_WINDOW_H
