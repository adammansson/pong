#include <math.h>
#include "vector.h"

double vec2f_length(vec2f_t *v)
{
    return sqrt((v->x)*(v->x) + (v->y)*(v->y));
}

void vec2f_normalize(vec2f_t *v)
{
    double len = vec2f_length(v);
    v->x /= len;
    v->y /= len;
}

void vec2f_scale(vec2f_t *v, int scalar)
{
    v->x *= scalar;
    v->y *= scalar;
}

void vec2f_rotate(vec2f_t *v, double angle)
{
    double len = vec2f_length(v);
    v->x = cos(angle);
    v->y = sin(angle);
    vec2f_scale(v, len);
}
