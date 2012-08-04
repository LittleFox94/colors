#ifndef UC_PROGRESSBAR_H
#define UC_PROGRESSBAR_H

#include "usercontrol.h"


class UC_ProgressBar : public UserControl
{
	public:
		UC_ProgressBar(int min, int max, int x, int y, int w, int h);
		virtual ~UC_ProgressBar();

		void Draw(sf::RenderTarget *window);

		int Value;
		int Min;
		int Max;
	protected:
	private:
		unsigned int _aniState;
		sf::Image _aniImg;
		sf::Sprite _aniSprite;
};

#endif // UC_PROGRESSBAR_H
