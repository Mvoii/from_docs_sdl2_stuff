#include "header.h"

int main(int argc, char *args[])
{
    // the window we'll be rendering to
    SDL_Window *window = NULL;

    // the surface contained by the window
    SDL_Surface *screenSurface = NULL;

    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create window
        window = SDL_CreateWindow("SDL tut", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            // get window surface
            screenSurface = SDL_GetWindowSurface(window);

            // fill teh surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0xFF));

            // update the surface
            SDL_UpdateWindowSurface(window);

            // hack to get window to stay
            SDL_Event e;
            bool quit = false;
            while (quit == false)
            {
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }
            }
        }
    }
    // Destroy the window
    SDL_DestroyWindow(window);

    //  Quit SDL subsystems
    SDL_Quit();

    return (0);
}
