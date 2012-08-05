#include "include/newgameform.h"

NewGameForm::NewGameForm(void *cancelHandler)
{
    Title = "Neues Spiel";
    Width = 400;
    Height = 300;

    _titleLabel = new UC_Label("Neues Spiel", sf::Color(0, 0, 0), 24, 5, 5);
    Gui()->AddItem(_titleLabel);

    _numPlayersLabel = new UC_Label("Spieleranzahl:", sf::Color(0, 0, 0), 12, 5, 52);
    Gui()->AddItem(_numPlayersLabel);

    _numPlayers = new UC_ComboBox(140, 50, 120);
    _numPlayers->AddItem("2");
    _numPlayers->AddItem("3");
    _numPlayers->AddItem("4");
    _numPlayers->SetCurrentIndex(0);
    Gui()->AddItem(_numPlayers);

    _numColorsLabel = new UC_Label("Farbenanzahl:", sf::Color(0, 0, 0), 12, 5, 82);
    Gui()->AddItem(_numColorsLabel);

    _numColors = new UC_ComboBox(140, 80, 120);
    _numColors->AddItem("4 (Leicht)");
    _numColors->AddItem("5");
    _numColors->AddItem("6");
    _numColors->AddItem("7");
    _numColors->AddItem("8");
    _numColors->AddItem("9");
    _numColors->AddItem("10 (Sehr Schwer)");
    _numColors->SetCurrentIndex(0);
    Gui()->AddItem(_numColors);

    _createGameButton = new UC_Button("res/img/gui/button.png", "Spiel starten", 400 - 125, 280 - 30, NULL);
    Gui()->AddItem(_createGameButton);

    _cancelButton = new UC_Button("res/img/gui/button.png", "Abbrechen", 400 - 250, 280 - 30, cancelHandler, (void*)this);
    Gui()->AddItem(_cancelButton);
}

NewGameForm::~NewGameForm()
{
    _titleLabel->Dispose();
    _numPlayersLabel->Dispose();
    _numPlayers->Dispose();
    _numColorsLabel->Dispose();
    _numColors->Dispose();
    _createGameButton->Dispose();
    _cancelButton->Dispose();

    delete _titleLabel;
    delete _numPlayersLabel;
    delete _numPlayers;
    delete _numColorsLabel;
    delete _numColors;
    delete _createGameButton;
    delete _cancelButton;
}
