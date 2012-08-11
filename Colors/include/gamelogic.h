#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "stdio.h"

static const unsigned char DefaultPalette[][3] =
{
	{ 255,	0,		0	},
	{ 0,	255,	0	},
	{ 0,	0,		255	},
	{ 255,	255,	0	},
	{ 255,	0,		255	},
	{ 0,	255,	255	},
	{ 255,	255,	255	},
	{ 0,	0,		0	},
	{ 127,	0,		0	},
	{ 0,	127,	0	},
	{ 0,	0,		127	},
	{ 127,	127,	0	},
	{ 127,	0,		127	},
	{ 0,	127,	127	},
	{ 192,	192,	192	},
	{ 63,	63,		63	}
};

class GameLogic
{
    public:
        GameLogic(int width, int height, int numColors);
        virtual ~GameLogic();

        char GetColor(int x, int y);
        void SetColor(int x, int y, char color);
        void Render(sf::RenderWindow *window);

    protected:
    private:
        char **_field;
        unsigned char *_pictureBuffer;

        int _width;
        int _height;

        sf::Image *_image;
        sf::Sprite *_sprite;
        sf::Clock *_clock;
};

#endif // GAMELOGIC_H
