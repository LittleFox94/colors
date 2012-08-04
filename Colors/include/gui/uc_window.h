#ifndef UC_WINDOW_H
#define UC_WINDOW_H

#include "usercontrol.h"

struct UC_WINDOW_ITEM
{
	UserControl *control;
	struct UC_WINDOW_ITEM *next;
};


class UC_Window : public UserControl
{
	public:
		UC_Window();
		virtual ~UC_Window();

		void Draw(sf::RenderTarget *);
		void AddItem(UserControl*);
		void OnHover(int, int, GUI*);
		void OnClick(int, int, GUI*);
		void OnUnclick(int, int, GUI*);
		bool IsMovable();
		void Dispose();
		void OnKeyPressed(char);

		string Title;
	protected:
	private:
		struct UC_WINDOW_ITEM *_item;
		struct UC_WINDOW_ITEM *_focusedItem;
		bool _itemFound;
};

#endif // UC_WINDOW_H
