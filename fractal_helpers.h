#ifndef FRACTAL_HELPERS_H
#define FRACTAL_HELPERS_H

#include <vector>
#include <OpenGL/gl.h>

#include "geometries.h"

GLfloat*
convert_to_arrayf(std::vector<struct Triangle> triangles);

GLfloat*
convert_to_arrayf(std::vector<struct Quad> quads);

GLfloat*
extract_tex_coords(GLfloat* data, size_t entry_count);

GLfloat*
extract_colors(GLfloat* data, size_t entry_count);

GLfloat*
extract_normals(GLfloat* data, size_t entry_count);

GLfloat*
extract_vertices(GLfloat* data, size_t entry_count);

#endif
