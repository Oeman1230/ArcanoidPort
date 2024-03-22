
This project made for educational purposes.

This program is a port of my game from Java Courses to C++ language. "OEFrames" was inspired by Java Swing API.
Goal of a project is to port the game from Java language to C++ with minimum changes in source code and architecture of the game.

Program made by using Microsoft Visual Studio 2019

External libraries: SDL2.0, SDL_image, SDL_ttf, SDL_gfx

To compile program use cmake. 

mkdir build <br/>
cd build <br/>
cmake .. <br/>
cmake --build . <br/>

After build copy SDL2_gfx.dll file to ArcanoidPort.exe directory<br/>
src/SDL2_gfx_lib/SDL2_gfx.dll   ->   build/Debug/
