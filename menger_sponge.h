#ifndef MENGER_SPONGE_H 
#define MENGER_SPONGE_H 

#include <vector>

#include "geometries.h"

std::vector<struct Quad> 
create_menger_sponge(struct Cube base, unsigned int depth);

#endif

