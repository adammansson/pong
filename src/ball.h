#include <SDL2/SDL.h>

typedef struct ball {
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect rect;
    int side;
    float x_pos, y_pos;
} ball_t;

ball_t *create_ball(SDL_Renderer *renderer, int side, int x0, int y0);

void render_ball(SDL_Renderer *renderer, ball_t *ball);

void move_ball(ball_t *ball);
