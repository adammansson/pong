#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "ball.h"
#include "paddle.h"

#define WINDOW_WIDTH (800)
#define WINDOW_HEIGHT (600)

int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    bool close_requested;

    ball_t *ball;
    paddle_t *paddle0;
    paddle_t *paddle1;

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

    ball = create_ball(renderer, 80, 300, 100);
    paddle0 = create_paddle(renderer, 60, 120, 40, 100);
    paddle1 = create_paddle(renderer, 60, 120, 500, 100);

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

        move_ball(ball);
        move_paddle(paddle0);
        move_paddle(paddle1);

        render_ball(renderer, ball);
        render_paddle(renderer, paddle0);
        render_paddle(renderer, paddle1);
        SDL_RenderPresent(renderer);
        
        SDL_Delay(1000/60);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
