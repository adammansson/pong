typedef struct vec2f {
    double x, y;
} vec2f_t;

double length(vec2f_t *v);

void normalize(vec2f_t *v);

void scale(vec2f_t *v, int scalar);

void rotate(vec2f_t *v, double angle);
