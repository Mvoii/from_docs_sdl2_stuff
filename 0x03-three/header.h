#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

// screen dimensions
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// the window we'll be rendering to
extern SDL_Window *gWindow;
// surface contained by the window
extern SDL_Surface *gScreenSurface;
// image we will load and show the screen
extern SDL_Surface *gHelloWorld;

// starts up sdl and creates a window
bool init();

// loads media
bool loadMedia();

// free subsys and shut sdl
void close();

#endif
