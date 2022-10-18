#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include "vector.h"

#define WINDOW_WIDTH (580)
#define WINDOW_HEIGHT (400)
#define BALL_SIDE (20)
#define BALL_SPEED (8)
#define PADDLE_WIDTH (20)
#define PADDLE_HEIGHT (70)
#define SSG_WIDTH (25)

extern void draw_ssg(SDL_Renderer *renderer, unsigned char n, int x0, int y0, int width);

int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    bool close_requested;
    close_requested = false;
    bool l_up, l_down, r_up, r_down;
    l_up = false; l_down = false; r_up = false; r_down = false;
    int l_points, r_points;
    l_points = 0; r_points = 0;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer))
    {
        printf("error creating window or renderer: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    vec2f_t ball_pos = { .x=(WINDOW_WIDTH/2 - BALL_SIDE/2), .y=(WINDOW_HEIGHT/2 - BALL_SIDE/2) };
    vec2f_t ball_vel = { .x=-BALL_SPEED, .y=0.0 };
    SDL_Rect ball = { .x=(WINDOW_WIDTH/2 - BALL_SIDE/2), .y=(WINDOW_HEIGHT/2 - BALL_SIDE/2), .w=BALL_SIDE, .h=BALL_SIDE };

    SDL_Rect l_paddle = { .x=(50 - PADDLE_WIDTH/2), .y=(WINDOW_HEIGHT/2 - PADDLE_HEIGHT/2), .w=PADDLE_WIDTH, .h=PADDLE_HEIGHT };
    SDL_Rect r_paddle = { .x=(WINDOW_WIDTH - 50 - PADDLE_WIDTH/2), .y=(WINDOW_HEIGHT/2 - PADDLE_HEIGHT/2), .w=PADDLE_WIDTH, .h=PADDLE_HEIGHT };

    // game loop
    while (!close_requested)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    close_requested = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_W:
                            l_up = true;
                            break;
                        case SDL_SCANCODE_UP:
                            r_up = true;
                            break;
                        case SDL_SCANCODE_S:
                            l_down = true;
                            break;
                        case SDL_SCANCODE_DOWN:
                            r_down = true;
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_W:
                            l_up = false;
                            break;
                        case SDL_SCANCODE_UP:
                            r_up = false;
                            break;
                        case SDL_SCANCODE_S:
                            l_down = false;
                            break;
                        case SDL_SCANCODE_DOWN:
                            r_down = false;
                            break;
                    }
                    break;
            }
        }

        if (l_up && !l_down && l_paddle.y >= 0) l_paddle.y -= 5;
        if (!l_up && l_down && l_paddle.y <= (WINDOW_HEIGHT - PADDLE_HEIGHT)) l_paddle.y += 5;
        if (r_up && !r_down && r_paddle.y >= 0) r_paddle.y -= 5;
        if (!r_up && r_down && r_paddle.y <= (WINDOW_HEIGHT - PADDLE_HEIGHT)) r_paddle.y += 5;

        if (ball_pos.y <= 0 || ball_pos.y >= WINDOW_HEIGHT - BALL_SIDE) 
        {
            ball_vel.y *= -1;
        } 

        if (SDL_HasIntersection(&ball, &l_paddle) == SDL_TRUE)
        {
            int diff = ((ball_pos.y + BALL_SIDE/2) - (l_paddle.y + PADDLE_HEIGHT/2));

            ball_pos.x += 5;
            vec2f_set_angle(&ball_vel, (M_PI / 32) * (diff / 5));
            vec2f_scale(&ball_vel, BALL_SPEED);
        }

        if (SDL_HasIntersection(&ball, &r_paddle) == SDL_TRUE)
        {
            int diff = ((ball_pos.y + BALL_SIDE/2) - (r_paddle.y + PADDLE_HEIGHT/2));

            ball_pos.x -= 5;
            vec2f_set_angle(&ball_vel, (-M_PI / 32.0) * (diff / 5) + M_PI);
            vec2f_scale(&ball_vel, BALL_SPEED);
        }

        if (ball_pos.x + BALL_SIDE <= 0)
        {
            ball_pos.x=(WINDOW_WIDTH/2 - BALL_SIDE/2);
            ball_pos.y=(WINDOW_HEIGHT/2 - BALL_SIDE/2);
            l_points++;
        }

        if (ball_pos.x >= WINDOW_WIDTH)
        {
            ball_pos.x=(WINDOW_WIDTH/2 - BALL_SIDE/2);
            ball_pos.y=(WINDOW_HEIGHT/2 - BALL_SIDE/2);
            r_points++;
        }

        /* printf("%f\n", vec2f_length(&ball_vel)); */

        ball_pos.x += ball_vel.x;
        ball_pos.y += ball_vel.y;

        ball.x = (int) ball_pos.x;
        ball.y = (int) ball_pos.y;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &ball);
        SDL_RenderFillRect(renderer, &l_paddle);
        SDL_RenderFillRect(renderer, &r_paddle);

        draw_ssg(renderer, l_points, 10, 10, SSG_WIDTH);
        draw_ssg(renderer, r_points, WINDOW_WIDTH - SSG_WIDTH - 10, 10, SSG_WIDTH);
        if (l_points >= 10 || r_points >= 10) return 0;

        SDL_RenderPresent(renderer);

        SDL_Delay(1000/60);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
