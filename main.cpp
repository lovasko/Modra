#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <functional>
#include <numeric>
#include <signal.h>

#include "floating.h"
#include "fractal_helpers.h"
#include "sierpinsky_tetrahedron.h"
#include "menger_sponge.h"
#include "geometries.h"
#include "enums.h"
#include "options.h"
#include "stats.h"

SDL_Surface *surface;
bool vbo_capable;
bool done;
bool is_active;
MyFloating angle;

MyFloating *data;
size_t data_block_count;
size_t data_block_size;
size_t data_point_count;
GLuint tex;

enum Fractal fractal = SIERPINSKY_TETRAHEDRON;
unsigned int fractal_depth = 5;
enum DrawingMethod drawing_method = IMMEDIATE;
enum ShadingMethod shading_method = SMOOTH;
enum VertexBuffer vertex_buffer = SEPARATE;
bool light_flag = false;
bool wireframe_flag = false;
bool texture_flag = false;
bool blending_flag = false;
std::vector<long> draw_times;
std::vector<long> swap_times;

void 
quit (int return_code)
{
  SDL_Quit();
	exit(return_code);
}

void
init_sdl ()
{
  const SDL_VideoInfo *video_info;


  if (SDL_Init( SDL_INIT_VIDEO ) < 0)
  {
    fprintf(stderr, "Video initialization failed: %s", SDL_GetError());
    quit(1);
  }

  video_info = SDL_GetVideoInfo();
  if (!video_info)
  {
    fprintf(stderr, "Video info query failed: %s", SDL_GetError());
    quit(1);
  }

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 0);

  surface = SDL_SetVideoMode(600, 600, 32, 
	    SDL_OPENGL | SDL_GL_DOUBLEBUFFER);

  if (!surface)
  {
    fprintf(stderr, "Video mode set failed: %s", SDL_GetError());
    quit(1);
  }
}

void
resize_viewport ()
{
  glViewport(0, 0, 600, 600);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(50.0f, 1.0f, 1.0f, 20.0f);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

GLubyte*
generate_texture ()
{
	GLubyte *result;

	result = (GLubyte*)malloc(sizeof(GLubyte) * 64 * 64 * 4);
	memset(result, 255, 64*64*4);

	for (int i = 0; i < 64 * 64 * 4; i++)
	{
		if (i % 4 == 0)
		{
			int xy = i/4;
			int x = xy / 64 - 32;
			int y = xy % 64 - 32;

			if (y*y + x*x< 32*32)
			{
				result[i+0] = (sin(x))*255;
				result[i+1] = (sin(y))*255;
				result[i+2] = (sin(x))*255;
				result[i+3] = 32;
			}
		}
	}

	return result;
}

void
init_opengl ()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(20.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	resize_viewport();

	if (blending_flag)
	{
		glDisable(GL_DEPTH_TEST);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	if (wireframe_flag)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		
	}

	if (light_flag)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_NORMALIZE);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

		GLfloat ambientLight[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
		GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
		GLfloat position[] = { 0.0f, 0.0f, 0.0f, 1.0f };

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, position);
	}

	if (texture_flag)
	{
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &tex); 
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

		GLubyte *pixels = generate_texture();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA,
		    GL_UNSIGNED_BYTE, pixels);

	}

	switch (shading_method)
	{
		case FLAT:
			glShadeModel(GL_FLAT);
		break;

		case SMOOTH:
			glShadeModel(GL_SMOOTH);
		break;

		default:
		break;
	}
}

void
init_extensions ()
{
	vbo_capable = false;

  GLenum err = glewInit();
  if (err != GLEW_OK)
  {
    printf("GLEW initialization error: %s\n", glewGetErrorString(err));
    return;
  }

  vbo_capable = GL_ARB_vertex_buffer_object;
}

void
init_animation ()
{
	angle = 0.0f;
}

void
step_animation ()
{
	angle += 0.02f;
}

void
apply_animation ()
{
	glRotatef(angle, 0.0, 1.0, 0.0);
}

void
draw_scene ()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -10.0f + sin(angle/10.0) * 0.75);
	apply_animation();
	glScalef(2.6, 2.6, 2.6);

	if (drawing_method == IMMEDIATE)
	{
		if (fractal == SIERPINSKY_TETRAHEDRON)
		{
			glBindTexture(GL_TEXTURE_2D, tex);
			glBegin(GL_TRIANGLES);
				for (unsigned int i = 0; i < data_block_count; i++)
				{
					unsigned int k = i * 36;

					if (texture_flag)
						myTexCoord2v(data + k + 0);
					myColor4v(data + k + 2);
					if (light_flag)
						myNormal3v(data + k + 6);
					myVertex3v(data + k + 9);

					if (texture_flag)
						myTexCoord2v(data + k + 12);
					myColor4v(data + k + 14);
					if (light_flag)
						myNormal3v(data + k + 18);
					myVertex3v(data + k + 21);

					if (texture_flag)
						myTexCoord2v(data + k + 24);
					myColor4v(data + k + 26);
					if (light_flag)
						myNormal3v(data + k + 30);
					myVertex3v(data + k + 33);
				}
			glEnd();
		}
		else if (fractal == MENGER_SPONGE)
		{
			glBegin(GL_QUADS);
				for (unsigned int i = 0; i < data_block_count; i++)
				{
					unsigned int k = i * 48;

					if (texture_flag)
						myTexCoord2v(data + k + 0);
					myColor4v(data + k + 2);
					if (light_flag)
						myNormal3v(data + k + 6);
					myVertex3v(data + k + 9);

					if (texture_flag)
						myTexCoord2v(data + k + 12);
					myColor4v(data + k + 14);
					if (light_flag)
						myNormal3v(data + k + 18);
					myVertex3v(data + k + 21);

					if (texture_flag)
						myTexCoord2v(data + k + 24);
					myColor4v(data + k + 26);
					if (light_flag)
						myNormal3v(data + k + 30);
					myVertex3v(data + k + 33);

					if (texture_flag)
						myTexCoord2v(data + k + 36);
					myColor4v(data + k + 38);
					if (light_flag)
						myNormal3v(data + k + 42);
					myVertex3v(data + k + 45);
				}
			glEnd();
		}
		else
		{
			glClearColor(1.0, 0.0, 0.0, 1.0);
		}
	}
	else if (drawing_method == VERTEX_BUFFER)
	{
		if (fractal == SIERPINSKY_TETRAHEDRON)
		{
			glDrawArrays(GL_TRIANGLES, 0, data_point_count);
		}
		else if (fractal == MENGER_SPONGE)
		{
			glDrawArrays(GL_QUADS, 0, data_point_count);
		}
	}

  glFlush();
}

int
main_loop()
{
	is_active = true;
	SDL_Event event;
	
	while (!done)
	{
		while ( SDL_PollEvent( &event ) )
		{
			switch ( event.type )
			{
				case SDL_ACTIVEEVENT:
					if ( event.active.state == SDL_APPACTIVE )
						is_active = (event.active.gain != 0);
					break;

				case SDL_QUIT:
					done = true;
					break;

				default:
					break;
			}
		}

		if (is_active)
		{
			step_animation();

			using namespace std::chrono;

			auto start = high_resolution_clock::now();
			draw_scene();
			auto end = high_resolution_clock::now();
			auto delta = duration_cast<microseconds>(end - start).count();
			draw_times.push_back(delta);

			start = high_resolution_clock::now();
			SDL_GL_SwapBuffers();
			end = high_resolution_clock::now();
			delta = duration_cast<microseconds>(end - start).count();
			swap_times.push_back(delta);
		}
	}
	
	return EXIT_SUCCESS;
}

void
print_test_setup ()
{
	std::cout << "Object: " << (fractal == SIERPINSKY_TETRAHEDRON ? "Sierpinsky"
	    " Tetrahedron" : "Menger Sponge") << " (" << data_block_count << 
	    " primitives)"<< std::endl;
	std::cout << "Shading method: " << (shading_method == FLAT ? "Flat" :
	    "Smooth") << ", ";
	std::cout << "Drawing method: " << (drawing_method == IMMEDIATE ? 
	    "Immediate" : (drawing_method == VERTEX_BUFFER ? "Vertex buffer" : 
	    "Index buffer"));
	
	if (drawing_method == VERTEX_BUFFER || drawing_method == INDEX_BUFFER)
	    std::cout << std::endl << "Vertex buffer type: " << 
			(vertex_buffer == SEPARATE ?  "Separate" : "Interleaved") << std::endl;

	std::cout << std::endl;
	std::cout << "Light: " << (light_flag ? "on" : "off");
	std::cout << ", Wireframe: " << (wireframe_flag ? "on" : "off");
	std::cout << ", Texture: " << (texture_flag ? "on" : "off");
	std::cout << ", Blending: " << (blending_flag ? "on" : "off");
	std::cout << std::endl;
}

void 
sigint_handler (int sig)
{
	(void) sig;

	std::cout << TypeName << std::endl;
	print_test_setup();
	print_stats(std::string("draw"), draw_times);
	print_stats(std::string("swap"), swap_times);
	std::cout << "---------------------------------------" << std::endl;
	done = true;
}

void 
catch_sigint()
{
	struct sigaction new_sa;
	struct sigaction old_sa;

	sigfillset(&new_sa.sa_mask);
	new_sa.sa_handler = sigint_handler;
	new_sa.sa_flags = 0;

	sigaction(SIGINT, &new_sa, 0);
}

int 
main (int argc, char *argv[])
{
	catch_sigint();
	parse_options(argc, argv);

	init_sdl();
	init_opengl();
	init_extensions();
	init_animation();

	if (fractal == SIERPINSKY_TETRAHEDRON)
	{
		Point a {{ 1.0,  1.0,  1.0}};
		Point b {{ 1.0, -1.0, -1.0}};
		Point c {{-1.0,  1.0, -1.0}};
		Point d {{-1.0, -1.0,  1.0}};

		struct Tetrahedron tetrahedron {a, b, c, d};
		std::vector<struct Triangle> triangles =
				create_sierpinsky_tetrahedron(tetrahedron, fractal_depth);

		data = convert_to_arrayf(triangles);
		data_block_count = triangles.size();
		data_point_count = data_block_count * 3;
	}
	else if (fractal == MENGER_SPONGE)
	{
		Point a {{-1.0, -1.0, -1.0}};
		Point b {{1.0, -1.0, -1.0}};
		Point c {{1.0, -1.0, 1.0}};
		Point d {{-1.0, -1.0, 1.0}};
		Point e {{-1.0, 1.0, -1.0}};
		Point f {{1.0, 1.0, -1.0}};
		Point g {{1.0, 1.0, 1.0}};
		Point h {{-1.0, 1.0, 1.0}};

		struct Cube cube {a, b, c, d, e, f, g, h};
		std::vector<struct Quad> quads = 
				create_menger_sponge(cube, fractal_depth);
		data = convert_to_arrayf(quads);
		data_block_count = quads.size();
		data_point_count = data_block_count * 4;
	}
	else
	{
		quit(0);
	}

	if (drawing_method == VERTEX_BUFFER)
	{
		if (vertex_buffer == INTERLEAVED)
		{
			glInterleavedArrays(GL_T2F_C4F_N3F_V3F, 0, data);
		}
		else if (vertex_buffer == SEPARATE)
		{
			if (texture_flag)
			{
				MyFloating *tex_coords_data = extract_tex_coords(data, data_point_count);
				glTexCoordPointer(2, MY_FLOATING, 0, tex_coords_data);
			}

			MyFloating *colors_data = extract_colors(data, data_point_count);
			glColorPointer(4, MY_FLOATING, 0, colors_data);

			if (light_flag)
			{
				MyFloating *normals_data = extract_normals(data, data_point_count);
				glNormalPointer(MY_FLOATING, 0, normals_data);
			}

			MyFloating *vertices_data = extract_vertices(data, data_point_count);
			glVertexPointer(3, MY_FLOATING, 0, vertices_data);
		}
	}

	return main_loop();
}

