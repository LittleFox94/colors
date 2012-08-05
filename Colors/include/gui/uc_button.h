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
		virtual ~UC_Button();
		UC_Label *_label;

		void Draw(sf::RenderTarget *);
		void OnHover(int, int, GUI*);
		void OnUnhover(int, int, GUI*);
		void OnClick(int, int, GUI*);
		void OnUnclick(int, int, GUI*);
		void Dispose();
	protected:
	private:
		sf::Image _buttonImg;
		sf::Sprite _buttonSprite;
};

#endif // UC_BUTTON_H
