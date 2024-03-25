# Overview

![image](tetris.svg)

This is an implementation of the Tetris game for Arduino Uno. It should work on other Arduino boards as well, perhaps with minor changes to pin connections.

The game can be played via the UART serial interface. Arduino IDE isn't suited to send game commands since every key press must be followed with the Enter key. Instead, Python script `serial-display.py` is used to process commands.

When played via the UART serial interface, game should instantiate objects from `CmdReader` and `Board`. If necessary hardware is available, we instead use `KeypadReader` and `DotMatrixBoard`. For other hardware, suitable subclasses can be derived from `CmdReader` and `Board`.

The overall UML class diagram is shown above. Only the public methods and attributes are shown. We should note the following:
- There's no game class. This could be considered if there's more complex game logic such as pausing or restarting a game. Today we just press the hardware reset button to restart the game.
- A `Board` object can be associated with zero or one `Tetrimino` object. When there's no active falling Tetrimino, then its zero.
- To debug the code during development, define `DEBUG` flag in file `Common.h`.
