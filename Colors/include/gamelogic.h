#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "main.h"
#include "resizableimage.h"
#include "gui/gui.h"
#include "mainmenu.h"

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
        GameLogic(int numPlayers, int width, int height, int numColors, bool allowRegions, bool diagonalFill, bool ai=true);
        virtual ~GameLogic();

        char GetColor(int x, int y, char **field);
        void SetColor(int x, int y, char color, char **field);
        void Render(sf::RenderWindow *window);
        void Fill(char color);
        int Fill(char color, int x, int y, char **field);

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
        int _numColors;

        int *_points;

        sf::Image *_image;
        sf::Sprite *_sprite;
        sf::Clock *_clock;

        ResizableImage *_panelBackground;

        GUI *_gui;

        UC_Label **_pointLabels;

        bool _gameFinished;
        int _winner;

        bool _ai;
        bool _doingAI;
        bool _diagonalFill;

        void GetPlayerPosition(int player, int *x, int *y);
        void DoAI();
        int Count(char color, int x, int y);
        bool ColorUsable(char color);
};

#endif // GAMELOGIC_H
