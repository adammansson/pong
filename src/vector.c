#include <math.h>
#include "vector.h"

double vec2f_length(vec2f_t *v)
{
    return sqrt((v->x)*(v->x) + (v->y)*(v->y));
}

double vec2f_angle(vec2f_t *v)
{
    return atan(v->y / v->x);
}

void vec2f_normalize(vec2f_t *v)
{
    double length = vec2f_length(v);
    v->x /= length;
    v->y /= length;
}

void vec2f_scale(vec2f_t *v, int scalar)
{
    v->x *= scalar;
    v->y *= scalar;
}

void vec2f_set_length(vec2f_t *v, double length)
{
    v->x = cos(vec2f_angle(v)) * length;
    v->y = sin(vec2f_angle(v)) * length;
}

void vec2f_set_angle(vec2f_t *v, double angle)
{
    v->x = cos(angle);
    v->y = sin(angle);
}

