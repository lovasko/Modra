#include <stdlib.h>
#include <iostream>

#include "fractal_helpers.h"

// GL_T2F_C4F_N3F_V3F
MyFloating*
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
	MyFloating *result = (MyFloating*)malloc(sizeof(MyFloating) * size);

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

MyFloating*
convert_to_arrayf(std::vector<struct Quad> quads)
{
	size_t point_count = 12;
	size_t normal_count = 12;
	size_t color_count = 16;
	size_t texcoord_count = 8;
	size_t block_size = point_count + normal_count + color_count + texcoord_count;
	size_t block_size_4 = block_size/4;//3 + 3 + 4 + 2;

	size_t size = quads.size() * point_count * normal_count * color_count *
	    texcoord_count;
	MyFloating *result = (MyFloating*)malloc(sizeof(MyFloating) * size);

	for (unsigned int i = 0; i < quads.size(); i++)
	{
		for (unsigned int k = 0; k < 4; k++)
		{
			result[(i * block_size_4 * 4) + k * block_size_4 + 0] = quads[i].points[k].tex_coord.coordinates[0];
			result[(i * block_size_4 * 4) + k * block_size_4 + 1] = quads[i].points[k].tex_coord.coordinates[1];

			result[(i * block_size_4 * 4) + k * block_size_4 + 2] = quads[i].points[k].color.components[0];
			result[(i * block_size_4 * 4) + k * block_size_4 + 3] = quads[i].points[k].color.components[1];
			result[(i * block_size_4 * 4) + k * block_size_4 + 4] = quads[i].points[k].color.components[2];
			result[(i * block_size_4 * 4) + k * block_size_4 + 5] = quads[i].points[k].color.components[3];

			result[(i * block_size_4 * 4) + k * block_size_4 + 6] = quads[i].points[k].normal.components[0];
			result[(i * block_size_4 * 4) + k * block_size_4 + 7] = quads[i].points[k].normal.components[1];
			result[(i * block_size_4 * 4) + k * block_size_4 + 8] = quads[i].points[k].normal.components[2];

			result[(i * block_size_4 * 4) + k * block_size_4 + 9] = quads[i].points[k].components[0];
			result[(i * block_size_4 * 4) + k * block_size_4 + 10] = quads[i].points[k].components[1];
			result[(i * block_size_4 * 4) + k * block_size_4 + 11] = quads[i].points[k].components[2];
		}
	}

	return result;
}

MyFloating*
extract_tex_coords(MyFloating* data, size_t entry_count)
{
	MyFloating *result;

	result = (MyFloating*)malloc(sizeof(MyFloating) * entry_count * 2);
	for (unsigned int i = 0; i < entry_count; i++)
	{
		result[i*2 + 0] = data[i*12 + 0];
		result[i*2 + 1] = data[i*12 + 1];
	}

	return result;
}

MyFloating*
extract_colors(MyFloating* data, size_t entry_count)
{
	MyFloating *result;

	result = (MyFloating*)malloc(sizeof(MyFloating) * entry_count * 4);
	for (unsigned int i = 0; i < entry_count; i++)
	{
		result[i*4 + 0] = data[i*12 + 2];
		result[i*4 + 1] = data[i*12 + 3];
		result[i*4 + 2] = data[i*12 + 4];
		result[i*4 + 3] = data[i*12 + 5];
	}

	return result;
}

MyFloating*
extract_normals(MyFloating* data, size_t entry_count)
{
	MyFloating *result;

	result = (MyFloating*)malloc(sizeof(MyFloating) * entry_count * 3);
	for (unsigned int i = 0; i < entry_count; i++)
	{
		result[i*3 + 0] = data[i*12 + 6];
		result[i*3 + 1] = data[i*12 + 7];
		result[i*3 + 2] = data[i*12 + 8];
	}

	return result;
}

MyFloating*
extract_vertices(MyFloating* data, size_t entry_count)
{
	MyFloating *result;

	result = (MyFloating*)malloc(sizeof(MyFloating) * entry_count * 3);
	for (unsigned int i = 0; i < entry_count; i++)
	{
		result[i*3 + 0] = data[i*12 + 9];
		result[i*3 + 1] = data[i*12 + 10];
		result[i*3 + 2] = data[i*12 + 11];
	}

	return result;
}
