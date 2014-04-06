#ifndef ENUMS_H
#define ENUMS_H

enum fractal_type
{
	SIERPINSKY_TETRAHEDRON,
	MENGER_SPONGE
};

enum drawing_method
{
	IMMEDIATE,
	VERTEX_BUFFER,
	INDEX_BUFFER
};

enum shading_method
{
	FLAT,
	SMOOTH
};

enum vertex_buffer_type
{
	SEPARATE,
	INTERLEAVED
};

enum floating_numbers_type
{
	SINGLE,
	DOUBLE
};

#endif

