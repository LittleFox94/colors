#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "main.h"
#include "resizableimage.h"
#include "gui/gui.h"

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
        GameLogic(int width, int height, int numColors, bool allowRegions);
        virtual ~GameLogic();

        char GetColor(int x, int y);
        void SetColor(int x, int y, char color);
        void Render(sf::RenderWindow *window);
        void Fill(char color);
        void Fill(char color, int x, int y);

        static void ButtonClick(void *param1, void *param2);

        GUI *GetGui();

    protected:
    private:
        char **_field;
        unsigned char *_pictureBuffer;

        int _width;
        int _height;

        int _currentPlayer;
        int _numPlayers;

        sf::Image *_image;
        sf::Sprite *_sprite;
        sf::Clock *_clock;

        ResizableImage *_panelBackground;

        GUI *_gui;

        void GetPlayerPosition(int player, int *x, int *y);
};

#endif // GAMELOGIC_H
