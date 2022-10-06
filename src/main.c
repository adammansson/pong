#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)

int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect dstrect;
    SDL_Event event;
    bool close_requested;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer))
    {
        printf("error creating window or renderer: %s\n", SDL_GetError());
        return 1;
    }

    surface = SDL_CreateRGBSurfaceWithFormat(0, 80, 80, 64, SDL_PIXELFORMAT_RGBA32);
    if (!surface)
    {
        printf("error creating surface: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_QueryTexture(texture, NULL, NULL, &dstrect.w, &dstrect.h);
    dstrect.w /= 4;
    dstrect.h /= 4;

    dstrect.x = (WINDOW_WIDTH - dstrect.w) / 2;
    dstrect.y = (WINDOW_HEIGHT - dstrect.h) / 2;

    while (!close_requested)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                close_requested = true;
            }
        }

        SDL_RenderClear(renderer);
        
        SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        SDL_RenderPresent(renderer);
        
        SDL_Delay(1000/60);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
