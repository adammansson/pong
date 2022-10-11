#include <SDL2/SDL.h>

const unsigned char SEGMENTS[10][7] =
{
    {1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 1, 1, 0, 1},
    {1, 1, 1, 1, 0, 0, 1},
    {0, 1, 1, 0, 0, 1, 1},
    {1, 0, 1, 1, 0, 1, 1},
    {1, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1}
};

void draw_ssg(SDL_Renderer *renderer, unsigned char n, int x0, int y0, int width)
{
    const unsigned char *ssg = SEGMENTS[n];

    if (ssg[0])
    {
        SDL_RenderDrawLine(renderer, x0, y0, x0 + width, y0);
    }
    if (ssg[1])
    {
        SDL_RenderDrawLine(renderer, x0 + width, y0, x0 + width, y0 + width);
    }
    if (ssg[2])
    {
        SDL_RenderDrawLine(renderer, x0 + width, y0 + width, x0 + width, y0 + 2 * width);
    }
    if (ssg[3])
    {
        SDL_RenderDrawLine(renderer, x0, y0 + 2 * width, x0 + width, y0 + 2 * width);
    }
    if (ssg[4])
    {
        SDL_RenderDrawLine(renderer, x0, y0 + width, x0, y0 + 2 * width);
    }
    if (ssg[5])
    {
        SDL_RenderDrawLine(renderer, x0, y0, x0, y0 + width);
    }
    if (ssg[6])
    {
        SDL_RenderDrawLine(renderer, x0, y0 + width, x0 + width, y0 + width);
    }
}
