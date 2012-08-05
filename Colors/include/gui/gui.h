#ifndef GUI_H
#define GUI_H

#include "usercontrol.h"

#include "uc_button.h"
#include "uc_checkbox.h"
#include "uc_combobox.h"
#include "uc_label.h"
#include "uc_line.h"
#include "uc_lineedit.h"
#include "uc_progressbar.h"
#include "uc_window.h"

struct GUI_ITEM
{
	UserControl *control;
	struct GUI_ITEM *next;
	struct GUI_ITEM *last;
};

typedef struct GUI_ITEM GUI_ITEM_T;

class GUI
{
	public:
		GUI();
		virtual ~GUI();

		void DrawItems(sf::RenderTarget *);
		void AddItem(UserControl *control);
		void RemoveItem(UserControl *control);
		void HoverAtPos(int, int);
		void ClickAtPos(int, int);
		void UnclickAtPos(int, int);
		bool MoveControlAt(int x, int y, int oldX, int oldY);

		bool IsMoving;
		bool hasChanged;

		const GUI_ITEM_T *FocusedItem;
	protected:
	private:
		GUI_ITEM_T *_firstGuiItem;
		GUI_ITEM_T *_lastGuiItem;
};

#endif
