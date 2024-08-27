#ifndef DEMO_H
#define DEMO_H

#include <stdio.h>
#include <SDL2/SDL.h>

typedef struct SDL_Instance
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_Instance;

int init_instance(SDL_Instance *);
void draw_stuff(SDL_Instance instance);
int poll_events();

#endif
