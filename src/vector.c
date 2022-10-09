#include <math.h>
#include "vector.h"

double length(vec2f_t *v)
{
    return sqrt((v->x)*(v->x) + (v->y)*(v->y));
}

void normalize(vec2f_t *v)
{
    double len = length(v);
    v->x /= len;
    v->y /= len;
}

void scale(vec2f_t *v, int scalar)
{
    v->x *= scalar;
    v->y *= scalar;
}

void rotate(vec2f_t *v, double angle)
{
    double len = length(v);
    v->x = cos(angle);
    v->y = sin(angle);
    scale(v, len);
}
