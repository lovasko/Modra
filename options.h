#ifndef OPTIONS_H
#define OPTIONS_H

#include "enums.h"

extern enum fractal_type fractal;
extern unsigned int fractal_depth;
extern enum drawing_method drawing;
extern enum shading_method shading;
extern enum vertex_buffer_type vertex_buffer;
extern bool light_flag;
extern bool wireframe_flag;
extern bool texture_flag;
extern bool blending_flag;

void
parse_options (int argc, char *argv[]);

#endif
