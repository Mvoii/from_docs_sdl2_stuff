#include "header.h"

void close()
{
    // dealloc surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    // destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // quit sdl subsystems
    SDL_Quit();
}
