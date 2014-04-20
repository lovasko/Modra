#ifndef FRACTAL_HELPERS_H
#define FRACTAL_HELPERS_H

#include <vector>
#include <OpenGL/gl.h>

#include "floating.h"
#include "geometries.h"

MyFloating*
convert_to_arrayf(std::vector<struct Triangle> triangles);

MyFloating*
convert_to_arrayf(std::vector<struct Quad> quads);

MyFloating*
extract_tex_coords(MyFloating* data, size_t entry_count);

MyFloating*
extract_colors(MyFloating* data, size_t entry_count);

MyFloating*
extract_normals(MyFloating* data, size_t entry_count);

MyFloating*
extract_vertices(MyFloating* data, size_t entry_count);

#endif
