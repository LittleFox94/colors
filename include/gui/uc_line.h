#ifndef UC_LINE_H
#define UC_LINE_H

#include "usercontrol.h"


class UC_Line : public UserControl
{
	public:
		UC_Line(int x, int y, int w, bool vertical);
		virtual ~UC_Line();

		void Draw(sf::RenderTarget *);
	protected:
	private:
};

#endif // UC_LINE_H
