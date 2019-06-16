CC=g++
FLAGS=-std=c++11 -Wall -Wextra
LIBS=-lSDL2 -lSDL2_ttf
OUTPUT=matter
DEPS = src/main.cpp src/units.cpp src/ui/control.cpp src/ui/label.cpp src/ui/pushbutton.cpp src/ui/window.cpp src/ui/layout/box.cpp src/ui/layout/hbox.cpp src/ui/layout/vbox.cpp src/color.cpp

all:
	$(CC) $(FLAGS) -o $(OUTPUT) $(DEPS) $(LIBS)