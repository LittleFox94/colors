#ifndef UC_COMBOBOX_H
#define UC_COMBOBOX_H

#include "usercontrol.h"

struct COMBOBOX_ITEM
{
	string caption;
	int id;
	struct COMBOBOX_ITEM *next;
	struct COMBOBOX_ITEM *last;
};

class UC_ComboBox : public UserControl
{
	public:
		UC_ComboBox(int, int, int);
		virtual ~UC_ComboBox();

		void Draw(sf::RenderTarget*);
		void OnHover(int, int, GUI*);
		void OnUnhover(int, int, GUI*);
		void OnClick(int, int, GUI*);
		void OnUnclick(int, int, GUI*);
		void AddItem(string caption);
		void SetCurrentIndex(int);

		int CurrentIndex;
	protected:
	private:
		int _scrollOffset;
		int _hoveredItem;

		sf::Image *_buttonImg;
		sf::Sprite *_buttonSprite;
		bool _isOpened;
		struct COMBOBOX_ITEM *_firstItem;
		struct COMBOBOX_ITEM *_lastItem;
		struct COMBOBOX_ITEM *_currentItem;
};

#endif // UC_COMBOBOX_H
