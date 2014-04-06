#ifndef OPTIONS_H
#define OPTIONS_H

#include "enums.h"

extern enum Fractal fractal;
extern unsigned int fractal_depth;
extern enum DrawingMethod drawing_method;
extern enum ShadingMethod shading_method;
extern enum VertexBuffer vertex_buffer;
extern bool light_flag;
extern bool wireframe_flag;
extern bool texture_flag;
extern bool blending_flag;

void
parse_options (int argc, char *argv[]);

#endif
