typedef struct vec2f {
    double x, y;
} vec2f_t;

double vec2f_length(vec2f_t *v);

void vec2f_normalize(vec2f_t *v);

void vec2f_scale(vec2f_t *v, int scalar);

void vec2f_rotate(vec2f_t *v, double angle);
