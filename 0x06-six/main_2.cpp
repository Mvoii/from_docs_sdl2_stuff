#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

// loads individual image
SDL_Surface *loadSurface(char *path);

// screen to render on
SDL_Window *gWindow = NULL;

// surface by window
SDL_Surface *gScreenSurface = NULL;

// imaes corresponding to key presses
SDL_Surface *gStretchedSurface = NULL;

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not init! SDL_ERROR: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("SDL TUT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

/**
 * knows we have an array of pointers to SDL surfaes called gKeyPressSurfaces with all the imaged we want to load
 * 
 */
SDL_Surface *loadSurface(char *path)
{
    // load final optimized image
    SDL_Surface *optimizedSurface = NULL;

    // load image at specified path
    SDL_Surface *loadedSurface = SDL_LoadBMP(path);
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
    }
    else
    {
        // convert surface to sceen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if(optimizedSurface == NULL)
        {
            printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
        }

        // get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}

bool loadMedia()
{
    bool success = true;

    gStretchedSurface = loadSurface("stretch.bmp");
    if (gStretchedSurface == NULL)
    {
        printf("Unable to load the image as %s! SDL Error: %s\n", "04_key_presses/press.bmp", SDL_GetError());
        success = false;
    }

    return success;
}

void close()
{
    SDL_FreeSurface(gStretchedSurface);
    gStretchedSurface = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

int main (int argc, char *args[])
{
    if (!init())
    {
        printf("Failed to init!\n");
    }
    else
    {
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            SDL_Event e;   // event handler
            bool quit = false;  // main loop flag


            while (!quit)
            {
                // event handler
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    
                }

                // apply the image stretched
                SDL_Rect stretchRect;
                stretchRect.x = 0;
                stretchRect.y = 0;
                stretchRect.w = SCREEN_WIDTH;
                stretchRect.h = SCREEN_HEIGHT;
                SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchRect);
                
                // update window
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }
    close();
    return 0;
}
