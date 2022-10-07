#include <SDL2/SDL.h>
#include "paddle.h"

paddle_t *create_paddle(SDL_Renderer *renderer, int width, int height, int x0, int y0)
{
    paddle_t *paddle;
    paddle = malloc(sizeof(paddle_t));

    paddle->surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_FillRect(paddle->surface, NULL, SDL_MapRGB(paddle->surface->format, 255, 255, 255));
    paddle->texture = SDL_CreateTextureFromSurface(renderer, paddle->surface);
    SDL_FreeSurface(paddle->surface);
    SDL_QueryTexture(paddle->texture, NULL, NULL, &paddle->rect.w, &paddle->rect.h);

    paddle->width = width;
    paddle->height = height;
    paddle->rect.x = (float) x0;
    paddle->rect.y = (float) y0;

    return paddle;
}

void render_paddle(SDL_Renderer *renderer, paddle_t *paddle)
{
    SDL_RenderCopy(renderer, paddle->texture, NULL, &paddle->rect);
}

void move_paddle(paddle_t *paddle)
{
    paddle->y_pos += 1;
    paddle->rect.y = (int) paddle->y_pos;
}
