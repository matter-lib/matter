# matter

Matter is a UI framework that makes creating a fast cross-platform UI easy

## Usage

Based on the code that exists at present creating a window with a fullscreen button is as simple as this:

```
Window win = Window(window, renderer);

Label btn = PushButton();
btn.setText("Click Me");
win.setRootControl(&btn);
```

`main.cpp` functions as an example of the current point of the library. In future all SDL2 code will be abstracted in an `Application` class.

Once the codebase is at the minimum working stage documentation will be available.

## Building

A temporary `Makefile` is currently in place. Run `make` to build a debugging binary `matter`.

## Contributing

This project is in early stages so **contributing is more than welcome!** Please submit a pull request documenting what changes you have made and be sure to give `CODESTYLE.md` a quick read to stay consistent with the existing codebase.