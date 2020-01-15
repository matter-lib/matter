# matter

Matter is a UI framework that makes creating a fast cross-platform UI easy.

- `main.cpp` functions as an example of the current point of the library. In future all SDL2 code will be abstracted in a class. Build instructions for Unix and Windows can be found below.
- Once the codebase is at the minimum working stage documentation will be available.

## Usage

Based on the code that exists at present creating a window with a fullscreen button is as simple as this:

```
Window win = Window(window, renderer);

Label btn = PushButton();
btn.setText("Click Me");
win.setRootView(&btn);
```

## Building

While the library is being built `main.cpp` serves as the test sandbox and can be built using the following steps.

### Unix

1. Install `sdl2` and `sdl2_ttf` through your package manager or manually.
2. Run `make` in your terminal at the root of the project and `matter` will be built.

### Windows

1. [Install `mingw-get`](https://osdn.net/projects/mingw/releases/) and install the essentials, especially `mingw32-gcc-g++-bin` and `mingw32-make`.
2. Download the [SDL2 MinGW library](https://www.libsdl.org/download-2.0.php) and the [SDL2 TTF MinGW library](https://www.libsdl.org/projects/SDL_ttf/), extract the two archives and drag all files from the `i686` folder in both to your MinGW installation folder (most likely `C:\MinGW`).
3. Run `mingw32-make` in your terminal at the root of the project and `matter.exe` will be built.

## Contributing

This project is in early stages so **contributing is more than welcome!** Please submit a pull request documenting what changes you have made and be sure to give `CODESTYLE.md` a quick read to stay consistent with the existing codebase.