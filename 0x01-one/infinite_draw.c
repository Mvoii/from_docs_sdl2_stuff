#include "demo.h"

int main(void)
{
    SDL_Instance instance;

    if (init_instance(&instance) != 0)
        return 1;

    /*
     * C will always be awesome
     * this is an infinite loop
     */
    while ("C is awesome")
    {
        SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
        SDL_RenderClear(instance.renderer);
        if (poll_events() == 1)
            break;
        /* draw stuff here */
        draw_stuff(instance);
        SDL_RenderPresent(instance.renderer);
    }
    SDL_DestroyRenderer(instance.renderer);
    SDL_DestroyWindow(instance.window);
    SDL_Quit();
    return (0);
}
