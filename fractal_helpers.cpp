#include <stdlib.h>
#include <iostream>

#include "fractal_helpers.h"

// GL_T2F_C4F_N3F_V3F
GLfloat*
convert_to_arrayf(std::vector<struct Triangle> triangles)
{
	size_t point_count = 9;
	size_t normal_count = 9;
	size_t color_count = 12;
	size_t texcoord_count = 6;
	size_t block_size = point_count + normal_count + color_count + texcoord_count;
	size_t block_size_3 = block_size/3;//3 + 3 + 4 + 2;

	size_t size = triangles.size() * point_count * normal_count * color_count *
	    texcoord_count;
	GLfloat *result = (GLfloat*)malloc(sizeof(GLfloat) * size);

	for (unsigned int i = 0; i < triangles.size(); i++)
	{
		for (unsigned int k = 0; k < 3; k++)
		{
			result[(i * block_size_3 * 3) + k * block_size_3 + 0] = triangles[i].points[k].tex_coord.coordinates[0];
			result[(i * block_size_3 * 3) + k * block_size_3 + 1] = triangles[i].points[k].tex_coord.coordinates[1];

			result[(i * block_size_3 * 3) + k * block_size_3 + 2] = triangles[i].points[k].color.components[0];
			result[(i * block_size_3 * 3) + k * block_size_3 + 3] = triangles[i].points[k].color.components[1];
			result[(i * block_size_3 * 3) + k * block_size_3 + 4] = triangles[i].points[k].color.components[2];
			result[(i * block_size_3 * 3) + k * block_size_3 + 5] = triangles[i].points[k].color.components[3];

			result[(i * block_size_3 * 3) + k * block_size_3 + 6] = triangles[i].points[k].normal.components[0];
			result[(i * block_size_3 * 3) + k * block_size_3 + 7] = triangles[i].points[k].normal.components[1];
			result[(i * block_size_3 * 3) + k * block_size_3 + 8] = triangles[i].points[k].normal.components[2];

			result[(i * block_size_3 * 3) + k * block_size_3 + 9] = triangles[i].points[k].components[0];
			result[(i * block_size_3 * 3) + k * block_size_3 + 10] = triangles[i].points[k].components[1];
			result[(i * block_size_3 * 3) + k * block_size_3 + 11] = triangles[i].points[k].components[2];
		}
	}

	return result;
}

