#ifndef GEOMETRIES_H
#define GEOMETRIES_H

#include <OpenGL/gl.h>

#include "floating.h"

struct Normal 
{
	MyFloating components[3];
};

struct Vector 
{
	union
	{
		MyFloating components[3];
		struct
		{
			MyFloating x;
			MyFloating y;
			MyFloating z;
		};
	};
};

struct TexCoord
{
	MyFloating coordinates[2];
};

struct Color
{
	MyFloating components[4];
};

struct Point
{
	union
	{
		MyFloating components[3];
		struct
		{
			MyFloating x;
			MyFloating y;
			MyFloating z;
		};
	};
	struct Normal normal;
	struct Color color;
	struct TexCoord tex_coord;
};

struct Triangle 
{
	struct Point points[3];
};

struct Quad 
{
	struct Point points[4];
};

struct Tetrahedron
{
	struct Point points[4];
};

struct Cube 
{
	struct Point points[8];
};

#endif
