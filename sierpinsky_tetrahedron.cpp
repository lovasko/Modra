#include "sierpinsky_tetrahedron.h"
#include <stack>
#include <iostream>
#include <map>
#include <cmath>

struct Normal
compute_normal (struct Vector a, struct Vector b)
{
	struct Normal result;
	result.components[0] = a.y * b.z - a.z * b.y;
	result.components[1] = a.z * b.x - a.x * b.z;
	result.components[2] = a.y * b.y - a.y * b.x;

	GLfloat length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	result.components[0] /= length;
	result.components[1] /= length;
	result.components[2] /= length;

	return result;
}

struct Vector
operator-(struct Point a, struct Point b)
{
	struct Vector result;
	result.x = a.components[0] - b.components[0];
	result.y = a.components[1] - b.components[1];
	result.z = a.components[2] - b.components[2];

	return result;
}

struct Color
random_color ()
{
	struct Color result;
	result.components[0] = (GLfloat)(rand() % 1000) / (GLfloat)999.0;
	result.components[1] = (GLfloat)(rand() % 1000) / (GLfloat)999.0;
	result.components[2] = (GLfloat)(rand() % 1000) / (GLfloat)999.0;
	result.components[3] = (GLfloat)0.5;

	return result;
}

std::vector<struct Triangle> 
create_sierpinsky_tetrahedron(struct Tetrahedron base, unsigned int depth)
{
	std::stack<std::pair<struct Tetrahedron, unsigned int>> stack;
	std::vector<struct Triangle> result;

	stack.push(std::make_pair(base, depth));
	while (!stack.empty())
	{
		std::pair<struct Tetrahedron, unsigned int> top = stack.top();	
		stack.pop();

		struct Point a = top.first.points[0];
		struct Point b = top.first.points[1];
		struct Point c = top.first.points[2];
		struct Point d = top.first.points[3];

		if (top.second == 0)
		{
			struct Normal n;
			struct Color color;
			struct TexCoord tc1 {{0.5, 0.0}};
			struct TexCoord tc2 {{0.0, 1.0}};
			struct TexCoord tc3 {{1.0, 1.0}};
			
			a.tex_coord = tc1;
			b.tex_coord = tc2;
			c.tex_coord = tc3;
			d.tex_coord = tc1;

			n = compute_normal(a - b, a - c); 
			a.normal = n;
			b.normal = n;
			c.normal = n;
			color = random_color();
			a.color = color;
			b.color = color;
			c.color = color;
			struct Triangle t1 {a, b, c};
			result.push_back(t1);

			n = compute_normal(a - b, a - d); 
			a.normal = n;
			b.normal = n;
			d.normal = n;
			color = random_color();
			a.color = color;
			b.color = color;
			d.color = color;
			struct Triangle t2 {a, b, d};
			result.push_back(t2);

			n = compute_normal(a - d, a - c); 
			a.normal = n;
			d.normal = n;
			c.normal = n;
			color = random_color();
			a.color = color;
			d.color = color;
			c.color = color;
			struct Triangle t3  {a, d, c};
			result.push_back(t3);

			n = compute_normal(b - c, b - d); 
			b.normal = n;
			c.normal = n;
			d.normal = n;
			color = random_color();
			b.color = color;
			c.color = color;
			d.color = color;
			struct Triangle t4 {b, c, d};
			result.push_back(t4);
		}
		else
		{
			struct Point ab, ac, ad;
			struct Point bc, bd;
			struct Point cd;

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

			struct Tetrahedron th1 {a, ab, ac, ad};
			stack.push(std::make_pair(th1, top.second - 1));

			struct Tetrahedron th2 {ab, b, bc, bd};
			stack.push(std::make_pair(th2, top.second - 1));

			struct Tetrahedron th3 {ac, bc, c, cd};
			stack.push(std::make_pair(th3, top.second - 1));

			struct Tetrahedron th4 {ad, bd, cd, d};
			stack.push(std::make_pair(th4, top.second - 1));
		}
	}

	return result;
}

