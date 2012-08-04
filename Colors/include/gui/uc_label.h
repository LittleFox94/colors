#ifndef UC_LABEL_H
#define UC_LABEL_H

#include "usercontrol.h"


class UC_Label : public UserControl
{
	public:
		UC_Label(string text, sf::Color color, int size, int x, int y);
		virtual ~UC_Label();

		void Draw(sf::RenderTarget *);
		void Dispose();
	protected:
	private:
		sf::String _s;
		sf::Font _font;
};

#endif // UC_LABEL_H
