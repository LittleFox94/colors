#ifndef UC_LINEEDIT_H
#define UC_LINEEDIT_H

#include "usercontrol.h"

class UC_LineEdit : public UserControl
{
	public:
		UC_LineEdit(int, int, int, int);
		virtual ~UC_LineEdit();

		void OnKeyPressed(char);
		void Draw(sf::RenderTarget *);
	protected:
	private:
		string _content;
		int aniState;
};

#endif // UC_LINEEDIT_H
