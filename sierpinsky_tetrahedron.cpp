#include "sierpinsky_tetrahedron.h"
#include <stack>
#include <iostream>
#include <map>

std::vector<struct triangle> 
create_sierpinsky_tetrahedron(struct tetrahedron th, unsigned int depth)
{
	std::stack<std::pair<struct tetrahedron, unsigned int>> stack;
	std::vector<struct triangle> result;

	stack.push(std::make_pair(th, depth));
	while (!stack.empty())
	{
		std::pair<tetrahedron, unsigned int> top = stack.top();	
		stack.pop();

		struct point a = top.first.points[0];
		struct point b = top.first.points[1];
		struct point c = top.first.points[2];
		struct point d = top.first.points[3];

		if (top.second == 0)
		{
			struct triangle t1 {a, b, c};
			result.push_back(t1);

			struct triangle t2 {a, b, d};
			result.push_back(t2);

			struct triangle t3  {a, d, c};
			result.push_back(t3);

			struct triangle t4 {b, c, d};
			result.push_back(t4);
		}
		else
		{
			struct point ab, ac, ad;
			struct point bc, bd;
			struct point cd;

			int j;

			for (j = 0; j < 3; j++) 
				ab.components[j] = (a.components[j] + b.components[j]) / 2.0;
			for (j = 0; j < 3; j++) 
				bc.components[j] = (b.components[j] + c.components[j]) / 2.0;
			for (j = 0; j < 3; j++) 
				ac.components[j] = (a.components[j] + c.components[j]) / 2.0;
			for (j = 0; j < 3; j++) 
				ad.components[j] = (a.components[j] + d.components[j]) / 2.0;
			for (j = 0; j < 3; j++) 
				bd.components[j] = (b.components[j] + d.components[j]) / 2.0;
			for (j = 0; j < 3; j++) 
				cd.components[j] = (c.components[j] + d.components[j]) / 2.0;

			struct tetrahedron th1 {a, ab, ac, ad};
			stack.push(std::make_pair(th1, top.second - 1));

			struct tetrahedron th2 {ab, b, bc, bd};
			stack.push(std::make_pair(th2, top.second - 1));

			struct tetrahedron th3 {ac, bc, c, cd};
			stack.push(std::make_pair(th3, top.second - 1));

			struct tetrahedron th4 {ad, bd, cd, d};
			stack.push(std::make_pair(th4, top.second - 1));
		}
	}

	return result;
}

