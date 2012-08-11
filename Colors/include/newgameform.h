#ifndef NEWGAMEFORM_H_INCLUDED
#define NEWGAMEFORM_H_INCLUDED

#include "gui/gui.h"

class NewGameForm : public UC_Window
{
    public:
        NewGameForm(void *cancelHandler, void *startHandler);
        virtual ~NewGameForm();

        int GetFieldWidth();
        int GetFieldHeight();
        int GetNumColors();
    protected:
    private:

        UC_ComboBox *_numPlayers;
        UC_ComboBox *_numColors;
        UC_ComboBox *_fieldSize;

        UC_Label *_titleLabel;
        UC_Label *_numPlayersLabel;
        UC_Label *_numColorsLabel;
        UC_Label *_fieldSizeLabel;

        UC_Button *_createGameButton;
        UC_Button *_cancelButton;
};

#endif // NEWGAMEFORM_H_INCLUDED
