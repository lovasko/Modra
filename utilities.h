#ifndef UTILITIES_H
#define UTILITIES_H

#include "geometries.h"

struct Normal
compute_normal (struct Vector a, struct Vector b);

struct Vector
operator-(struct Point a, struct Point b);

struct Color
random_color ();

#endif

