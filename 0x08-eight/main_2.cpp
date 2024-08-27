#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
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
SDL_Surface *gPNGSurface = NULL;

// loads individual image as texture
SDL_Texture *loadTexture(char *path);

// The window we'll be rendering to
SDL_Renderer *gRenderer = NULL;

// current displayed texture
SDL_Texture *gTexture = NULL;

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
        // set texture iltering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!\n");
        }
        gWindow = SDL_CreateWindow("SDL TUT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // init renderer
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // init renderer colour
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // init png loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_img could not be init! SDL_Error: %s\n", SDL_GetError());
                    success = false;
                }
            }
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
    SDL_Surface *loadedSurface = IMG_Load(path);
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

SDL_Texture *loadTexture(char *path)
{
    // the final texture
    SDL_Texture *newTexture = NULL;

    // Loadd image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
    }
    else
    {
        // Create texture from the surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

bool loadMedia()
{
    bool success = true;

    gTexture = loadTexture("texture.png");
    if (gTexture == NULL)
    {
        printf("Unable to load the texture image as %s! SDL Error: %s\n", "07_texture_loading_and_rendering/texture.bmp", SDL_GetError());
        success = false;
    }

    return success;
}

void close()
{
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
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
                // SDL_Rect stretchRect;
                // stretchRect.x = 0;
                // stretchRect.y = 0;
                // stretchRect.w = SCREEN_WIDTH;
                // stretchRect.h = SCREEN_HEIGHT;
                // SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchRect);

                // apply the png image
                // SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, NULL);
                
                // update window
                // SDL_UpdateWindowSurface(gWindow);

                // Clear screen
                SDL_RenderClear(gRenderer);

                // Render texture to screen
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                // Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    close();
    return 0;
}
