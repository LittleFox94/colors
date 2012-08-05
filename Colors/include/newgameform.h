#ifndef NEWGAMEFORM_H_INCLUDED
#define NEWGAMEFORM_H_INCLUDED

#include "gui/gui.h"

class NewGameForm : public UC_Window
{
    public:
        NewGameForm(void *cancelHandler);
        virtual ~NewGameForm();
    protected:
    private:

        UC_ComboBox *_numPlayers;
        UC_ComboBox *_numColors;

        UC_Label *_titleLabel;
        UC_Label *_numPlayersLabel;
        UC_Label *_numColorsLabel;

        UC_Button *_createGameButton;
        UC_Button *_cancelButton;
};

#endif // NEWGAMEFORM_H_INCLUDED
