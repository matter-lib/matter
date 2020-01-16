CC=g++
FLAGS=-std=c++11 -Wall -Wextra -g

LIBS=-lSDL2 -lSDL2_ttf
#ifdef __MINGW32__
	LIBS:=-lmingw32 -lSDL2main $(LIBS)
#endif

OUTPUT=matter
DEPS = src/main.cpp src/units.cpp src/ui/view.cpp src/ui/label.cpp src/ui/pushbutton.cpp src/ui/window.cpp src/ui/layout/box.cpp src/color.cpp

all:
	$(CC) $(FLAGS) -o $(OUTPUT) $(DEPS) $(LIBS)