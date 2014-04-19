#include "utilities.h"

#include <math.h>
#include <stdlib.h>

struct Normal
compute_normal (struct Vector a, struct Vector b)
{
	struct Normal result;
	result.components[0] = a.y * b.z - a.z * b.y;
	result.components[1] = a.z * b.x - a.x * b.z;
	result.components[2] = a.y * b.y - a.y * b.x;

	GLfloat length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	result.components[0] /= length;
	result.components[1] /= length;
	result.components[2] /= length;

	return result;
}

struct Vector
operator-(struct Point a, struct Point b)
{
	struct Vector result;
	result.x = a.components[0] - b.components[0];
	result.y = a.components[1] - b.components[1];
	result.z = a.components[2] - b.components[2];

	return result;
}

struct Color
random_color ()
{
	struct Color result;
	result.components[0] = (GLfloat)(rand() % 1000) / (GLfloat)999.0;
	result.components[1] = (GLfloat)(rand() % 1000) / (GLfloat)999.0;
	result.components[2] = (GLfloat)(rand() % 1000) / (GLfloat)999.0;
	result.components[3] = (GLfloat)0.5;

	return result;
}
