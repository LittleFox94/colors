#ifndef UC_BUTTON_H
#define UC_BUTTON_H

#include "usercontrol.h"
#include "uc_label.h"

class UC_Button : public UserControl
{
	public:
		void *callback;
		void *callbackParam;

		UC_Button();
		UC_Button(string imgFileName, int, int, void *cb = null);
		UC_Button(string imgFileName, string caption, int, int, void *cb = null);
		UC_Button(string imgFileName, int, int, void *cb, void *param);
		UC_Button(string imgFileName, string caption, int, int, void *cb, void *param);
		~UC_Button();

		void Draw(sf::RenderTarget *);
		void OnHover(int, int, GUI*);
		void OnUnhover(int, int, GUI*);
		void OnClick(int, int, GUI*);
		void OnUnclick(int, int, GUI*);
	protected:
	private:
		sf::Image *_buttonImg;
		sf::Sprite *_buttonSprite;
		UC_Label *_label;
};

#endif // UC_BUTTON_H
