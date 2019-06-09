CC=g++
CFLAGS=$(shell pkg-config --cflags sdl2 sdl2_ttf)
LIBS=$(shell pkg-config --libs sdl2 sdl2_ttf)
OUTPUT=matter
DEPS = src/main.cpp src/units.cpp src/ui/control.cpp src/ui/label.cpp src/ui/pushbutton.cpp src/ui/window.cpp src/ui/layout/box.cpp src/ui/layout/hbox.cpp src/ui/layout/vbox.cpp

all:
	$(CC) $(CFLAGS) -o $(OUTPUT) $(DEPS) $(LIBS) -Wall -Wextra