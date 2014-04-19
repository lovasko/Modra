#ifndef GEOMETRIES_H
#define GEOMETRIES_H

#include <OpenGL/gl.h>

struct Normal 
{
	GLfloat components[3];
};

struct Vector 
{
	union
	{
		GLfloat components[3];
		struct
		{
			GLfloat x;
			GLfloat y;
			GLfloat z;
		};
	};
};

struct TexCoord
{
	GLfloat coordinates[2];
};

struct Color
{
	GLfloat components[4];
};

struct Point
{
	union
	{
		GLfloat components[3];
		struct
		{
			GLfloat x;
			GLfloat y;
			GLfloat z;
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
