#ifndef ENUMS_H
#define ENUMS_H

enum Fractal
{
	SIERPINSKY_TETRAHEDRON,
	MENGER_SPONGE
};

enum DrawingMethod
{
	IMMEDIATE,
	VERTEX_BUFFER,
	INDEX_BUFFER
};

enum ShadingMethod
{
	FLAT,
	SMOOTH
};

enum VertexBuffer
{
	SEPARATE,
	INTERLEAVED
};

#endif

