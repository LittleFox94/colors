Colors:
	g++ src/gamelogic.cpp src/main.cpp src/mainmenu.cpp src/newgameform.cpp src/resizableimage.cpp src/gui/gui.cpp src/gui/uc_button.cpp src/gui/uc_checkbox.cpp src/gui/uc_combobox.cpp src/gui/uc_label.cpp src/gui/uc_line.cpp src/gui/uc_lineedit.cpp src/gui/uc_progressbar.cpp src/gui/uc_window.cpp src/gui/usercontrol.cpp -lsfml-graphics -lsfml-window -lsfml-system -o Colors

clean:
	rm Colors
