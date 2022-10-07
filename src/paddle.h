typedef struct paddle {
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect rect;
    int width, height;
    float x_pos, y_pos;
} paddle_t;

paddle_t *create_paddle(SDL_Renderer *renderer, int width, int height, int x0, int y0);

void render_paddle(SDL_Renderer *renderer, paddle_t *paddle);

void move_paddle(paddle_t *paddle);
