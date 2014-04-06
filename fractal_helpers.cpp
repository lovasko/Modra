#include <stdlib.h>
#include <iostream>

#include "fractal_helpers.h"

GLfloat*
convert_to_arrayf(std::vector<struct Triangle> triangles)
{
	size_t size = triangles.size() * 3 * 3;
	GLfloat *result = (GLfloat*)malloc(sizeof(GLfloat) * size);

	for (unsigned int i = 0; i < triangles.size(); i++)
	{
		for (unsigned int k = 0; k < 9; k++)
		{
			result[(i*9)+k] = triangles[i].points[k/3].components[k%3];
		}
	}

	return result;
}

