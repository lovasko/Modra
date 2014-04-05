#ifndef SIERPINSKY_TETRAHEDRON_H
#define SIERPINSKY_TETRAHEDRON_H

#include <vector>

#include "geometries.h"

std::vector<struct triangle> 
create_sierpinsky_tetrahedron(struct tetrahedron th, unsigned int depth);

#endif
