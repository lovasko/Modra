#ifndef FRACTAL_HELPERS_H
#define FRACTAL_HELPERS_H

#include <vector>
#include <OpenGL/gl.h>

#include "geometries.h"

GLfloat*
convert_to_arrayf(std::vector<struct triangle> triangles);

GLfloat*
convert_to_arrayf(std::vector<struct quad> quads);

#endif
