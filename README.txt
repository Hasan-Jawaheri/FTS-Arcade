Welcome to FTS Arcade! you don't want to know what FTS stands for, really.

===============================================================================
O V E R V I E W
===============================================================================
-------------------------------------------------------------------------------
FTS Arcade is a game emulator that provides an easy-to-use API in python. The
API provides basic functionality like loading and displaying images, along with
other game utilities like collision, input, and sound. Currently we only target
2D games (and specifically arcade games, hence the name). We would like to
build an arcade machine that runs only the emulator and allows users to install
games on it, written with the API.

What really happens behind the scenes is that the emulator basically waits for
a python script to run (which is a game written with the API). The script,
using the API, communicates with the emulator to have do rendering and
sprite management. With that being said, we are ashamed to announce that the
bottleneck right now is that it sends every sprite, piece of text and camera
to the emulator EVERY FRAME. This gets nasy when you have thousands of sprites.

The API is in an early stage and suggestions for improvement are welcome. If
you have any questions, suggestions or comments, feel free to contact the
authors.
-------------------------------------------------------------------------------
===============================================================================
H O W   T O   U S E
===============================================================================
-------------------------------------------------------------------------------
Put "FTS Python" and "FTS Collection" folders in your Documents (or
My Documents) folder. You probably don't want to modify the source code of the
emulator, but feel free to take a look. The code that you probably want to
modify/extend is in "FTS Python/API/".

To have a game running, there must be a folder in "Documents/FTS Collection/"
for the game. The name of this folder is the title of the game. Inside that
folder, the main file for the game has to have the same name as the folder,
followed by ".py" (e.g. "Ping Pong" folder should have "Ping Pong.py" as the
main code file). You are free to have any other files in the folder, like data
and code.
-------------------------------------------------------------------------------
===============================================================================
F I L E   S T R U C T U R E
===============================================================================
-------------------------------------------------------------------------------
@@ Root
This is the root of the project directory.
  > FTS Emulator
      This contains source code for the emulator. This will not compile
      without proper setup in Visual Studio and with the required libraries
      which can only be obtained from Hasan (see authors section).
      Feel free to inspect the code and contact me if you are interested in
      compiling it or if you want to request a change or an addition.
  > FTS Python
      This folder contains the API file structure, which is written in python.
  - Thumbs.db
      No clue why this is here. No clue how to get rid of it either.
  - function list.cpp
      Functions list that are part of the python API. The list is written in
      a C++-like format (for clarity), but they are normal python functions.
      The list is not complete. We aim to get the whole list functional before
      releasing the API.
-------------------------------------------------------------------------------
@@ FTS Python
This folder contains two folders. You HAVE to place them in your Documents (or
My Documents) in order for the API to work (it uses this directory to, uhh,
"compile" (kind of) your code).
  > FTS Arcade
      This folder contains the emulator executable (FTS Arcade.exe) and the
      API source code in python (inside API folder).
  > FTS Collection
      This folder is what the emulator looks for when listing the available
      games. Each subfolder here corresponds to a game that uses the API.
-------------------------------------------------------------------------------
===============================================================================
A U T H O R S
===============================================================================
Hasan Al-Jawaheri (H_B_A_J@hotmail.com)
Yusuf Musleh (ASK HIM TO PUT HIS EMAIL)

Copyright (c) 2014 Computing Club at CMUQ. Whatever that means.