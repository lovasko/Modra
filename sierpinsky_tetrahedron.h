#ifndef SIERPINSKY_TETRAHEDRON_H
#define SIERPINSKY_TETRAHEDRON_H

#include <vector>

#include "geometries.h"

std::vector<struct Triangle> 
create_sierpinsky_tetrahedron(struct Tetrahedron base, unsigned int depth);

#endif
