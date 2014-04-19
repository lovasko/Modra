#include "menger_sponge.h"
#include "utilities.h"

#include <stack>
#include <iostream>
#include <map>
#include <cmath>

struct Quad
make_quad (struct Point a, struct Point b, struct Point c, struct Point d)
{
	struct Point A = a;
	struct Point B = b;
	struct Point C = c;
	struct Point D = d;

	A.color = random_color();
	B.color = random_color();
	C.color = random_color();
	D.color = random_color();

	struct Normal normal = compute_normal(A - B, B - C);
	A.normal = normal;
	B.normal = normal;
	C.normal = normal;
	D.normal = normal;

	struct TexCoord tc1 {{0.0, 0.0}};
	struct TexCoord tc2 {{1.0, 0.0}};
	struct TexCoord tc3 {{1.0, 1.0}};
	struct TexCoord tc4 {{0.0, 1.0}};

	A.tex_coord = tc1;
	B.tex_coord = tc2;
	C.tex_coord = tc3;
	D.tex_coord = tc4;

	struct Quad result {A, B, C, D};
	return result;
}

struct Cube
cube_starting_with (int i, int j, int k, struct Point (*cube_points)[4][4])
{
	struct Cube result {
		cube_points[i+0][j+0][k+0], 
		cube_points[i+1][j+0][k+0],
		cube_points[i+1][j+0][k+1], 
		cube_points[i+0][j+0][k+1], 

		cube_points[i+0][j+1][k+0], 
		cube_points[i+1][j+1][k+0],
		cube_points[i+1][j+1][k+1], 
		cube_points[i+0][j+1][k+1], 
		};

	return result;
}

struct Point
lin_interpol (struct Point a, struct Point b, GLfloat tx, GLfloat ty, GLfloat
    tz)
{
	GLfloat new_x = a.x + (b.x - a.x) * tx;	
	GLfloat new_y = a.y + (b.y - a.y) * ty;	
	GLfloat new_z = a.z + (b.z - a.z) * tz;	
				
	std::cout << new_x << " " << new_y << " " <<  new_z << std::endl;

	struct Point result {new_x, new_y, new_z};
	return result;
}

std::vector<struct Quad> 
create_menger_sponge(struct Cube base, unsigned int depth)
{
	std::stack<std::pair<struct Cube, unsigned int>> stack;
	std::vector<struct Quad> result;
		
	stack.push(std::make_pair(base, depth));
	while (!stack.empty())
	{
		std::pair<struct Cube, unsigned int> top = stack.top();	
		stack.pop();

		struct Point a = top.first.points[0];
		struct Point b = top.first.points[1];
		struct Point c = top.first.points[2];
		struct Point d = top.first.points[3];
		struct Point e = top.first.points[4];
		struct Point f = top.first.points[5];
		struct Point g = top.first.points[6];
		struct Point h = top.first.points[7];

		if (top.second == 0)
		{
			result.push_back(make_quad(a, b, c, d));
			result.push_back(make_quad(e, f, g, h));
			result.push_back(make_quad(a, b, f, e));
			result.push_back(make_quad(c, d, h, g));
			result.push_back(make_quad(b, c, g, f));
			result.push_back(make_quad(a, d, h, e));
		}
		else
		{
			struct Point cube[4][4][4];
			for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
			{
				cube[i][j][k] = lin_interpol(a, g, 
					(GLfloat)i/3.0, 
					(GLfloat)j/3.0, 
					(GLfloat)k/3.0);

			}

			// cube front face
			struct Cube cf1 = cube_starting_with(0, 0, 0, cube);
			struct Cube cf2 = cube_starting_with(1, 0, 0, cube);
			struct Cube cf3 = cube_starting_with(2, 0, 0, cube);
			struct Cube cf4 = cube_starting_with(0, 1, 0, cube);
			struct Cube cf5 = cube_starting_with(2, 1, 0, cube);
			struct Cube cf6 = cube_starting_with(0, 2, 0, cube);
			struct Cube cf7 = cube_starting_with(1, 2, 0, cube);
			struct Cube cf8 = cube_starting_with(2, 2, 0, cube);

			// cube back face
			struct Cube cb1 = cube_starting_with(0, 0, 2, cube);
			struct Cube cb2 = cube_starting_with(1, 0, 2, cube);
			struct Cube cb3 = cube_starting_with(2, 0, 2, cube);
			struct Cube cb4 = cube_starting_with(0, 1, 2, cube);
			struct Cube cb5 = cube_starting_with(2, 1, 2, cube);
			struct Cube cb6 = cube_starting_with(0, 2, 2, cube);
			struct Cube cb7 = cube_starting_with(1, 2, 2, cube);
			struct Cube cb8 = cube_starting_with(2, 2, 2, cube);

			// cube side faces
			struct Cube cs1 = cube_starting_with(2, 0, 1, cube);
			struct Cube cs2 = cube_starting_with(2, 2, 1, cube);
			struct Cube cs3 = cube_starting_with(0, 0, 1, cube);
			struct Cube cs4 = cube_starting_with(0, 2, 1, cube);

			stack.push(std::make_pair(cf1, top.second-1));
			stack.push(std::make_pair(cf2, top.second-1));
			stack.push(std::make_pair(cf3, top.second-1));
			stack.push(std::make_pair(cf4, top.second-1));
			stack.push(std::make_pair(cf5, top.second-1));
			stack.push(std::make_pair(cf6, top.second-1));
			stack.push(std::make_pair(cf7, top.second-1));
			stack.push(std::make_pair(cf8, top.second-1));
			stack.push(std::make_pair(cb1, top.second-1));
			stack.push(std::make_pair(cb2, top.second-1));
			stack.push(std::make_pair(cb3, top.second-1));
			stack.push(std::make_pair(cb4, top.second-1));
			stack.push(std::make_pair(cb5, top.second-1));
			stack.push(std::make_pair(cb6, top.second-1));
			stack.push(std::make_pair(cb7, top.second-1));
			stack.push(std::make_pair(cb8, top.second-1));
			stack.push(std::make_pair(cs1, top.second-1));
			stack.push(std::make_pair(cs2, top.second-1));
			stack.push(std::make_pair(cs3, top.second-1));
			stack.push(std::make_pair(cs4, top.second-1));
		}
	}

	return result;
}

