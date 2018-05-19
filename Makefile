CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

SOURCES=src/gamelogic.cpp \
		src/main.cpp \
		src/mainmenu.cpp \
		src/newgameform.cpp \
		src/resizableimage.cpp \
		src/gui/gui.cpp \
		src/gui/uc_button.cpp \
		src/gui/uc_checkbox.cpp \
		src/gui/uc_combobox.cpp \
		src/gui/uc_label.cpp \
		src/gui/uc_line.cpp \
		src/gui/uc_window.cpp \
		src/gui/usercontrol.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=colors

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm ${OBJECTS}
	rm ${EXECUTABLE}
