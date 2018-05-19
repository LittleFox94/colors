#ifndef UC_CHECKBOX_H
#define UC_CHECKBOX_H

#include "usercontrol.h"
#include "gui.h"

class UC_CheckBox : public UserControl
{
	public:
		UC_CheckBox(string, int, int);
		virtual ~UC_CheckBox();

		void Draw(sf::RenderTarget *);
		void OnHover(int, int, GUI*);
		void OnUnhover(int, int, GUI*);
		void OnClick(int, int, GUI*);
		void OnUnclick(int, int, GUI*);

		bool Checked;
	protected:
	private:
		string _caption;
		sf::Font *_font;
		sf::Texture *_img;
		sf::Sprite *_sprite;
		sf::Text *_label;
};

#endif // UC_CHECKBOX_H
