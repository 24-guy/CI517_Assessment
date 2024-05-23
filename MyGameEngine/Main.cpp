//===================================================
//=== CI517 - Game Engine Fundamentals Assessment ===
//=============== Jay Gray, UoB 2024 ================
//===================================================

// Libraries to Include
#include <iostream>
#include <stdio.h>
#include "MyGame.h"
#include "MyMenuSubsystem.h"
using namespace std;

MyMenuSubsystem* menu = nullptr;

int main(int argc, char* argv[])
{
    const int frameDelay = 1000 / FPS;
    Uint64 frameStart = 0, frameTime = 0;

    menu = new MyMenuSubsystem;

    menu->startSDL("MenuTest");
    menu->welcomeScreen();
    menu->createBackground();

    try
    {
        menu->closeSDL();
        MyGame game;

        game.runMainLoop();
    }
    catch (exception e)
    {
        cout << "error: " << endl;
    }

    return 0;
}