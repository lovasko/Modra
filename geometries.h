#ifndef GEOMETRIES_H
#define GEOMETRIES_H

#include <OpenGL/gl.h>

struct point
{
	GLfloat components[3];
};

struct triangle 
{
	struct point points[3];
};

struct quad 
{
	struct point points[4];
};

struct tetrahedron
{
	struct point points[4];
};

#endif
