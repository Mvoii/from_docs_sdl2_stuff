#include "header.h"

int main(int argc, char *args[])
{
    // start up SDL and window
    if (!init())
    {
        printf("Failed to init!\n");
    }
    else
    {
        // load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            // apply the image
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

            // hack to get tthe window to stay up
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
    // free resources and close
    close();

    return 0;
}
