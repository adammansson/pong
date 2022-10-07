#include <SDL2/SDL.h>
#include "ball.h"

ball_t *create_ball(SDL_Renderer *renderer, int side, int x0, int y0)
{
    ball_t *ball;
    ball = malloc(sizeof(ball_t));

    ball->surface = SDL_CreateRGBSurfaceWithFormat(0, side, side, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_FillRect(ball->surface, NULL, SDL_MapRGB(ball->surface->format, 255, 255, 255));
    ball->texture = SDL_CreateTextureFromSurface(renderer, ball->surface);
    SDL_FreeSurface(ball->surface);
    SDL_QueryTexture(ball->texture, NULL, NULL, &ball->rect.w, &ball->rect.h);

    ball->side = side;
    ball->rect.x = (float) x0;
    ball->rect.y = (float) y0;

    return ball;
}

void render_ball(SDL_Renderer *renderer, ball_t *ball)
{
    SDL_RenderCopy(renderer, ball->texture, NULL, &ball->rect);
}

void move_ball(ball_t *ball)
{
    ball->y_pos += 1;
    ball->rect.y = (int) ball->y_pos;
}
