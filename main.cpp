#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include "fractal_helpers.h"
#include "sierpinsky_tetrahedron.h"
#include "opengl_properties.h"
#include "geometries.h"

SDL_Surface *surface;
bool vbo_capable;
bool done;
bool is_active;
GLfloat angle;

GLfloat *triangles;
size_t triangles_size;

enum drawing_method
{
	DIRECT,
	VERTEX_BUFFER,
	INDEX_BUFFER
};

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

void
init_opengl ()
{
  glShadeModel(GL_SMOOTH);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(20.0f);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	resize_viewport();
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

	glTranslatef(0.0, 0.0, -10.0f);
	apply_animation();
	glScalef(2.6, 2.6, 2.6);

	glColor3f(1.0, 0.6, 0.0);
	glBegin(GL_TRIANGLES);
			
		for (unsigned int i = 0; i < triangles_size; i++)
		{
			int k = i * 9;
			glVertex3fv(triangles + k);
			glVertex3fv(triangles + k + 3);
			glVertex3fv(triangles + k + 6);
		}

	glEnd();

  glFlush();
}

int
main_loop()
{
	done = false;
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

				case SDL_KEYDOWN:
					//handleKeyPress( &event.key.keysym );
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
			draw_scene();
			SDL_GL_SwapBuffers();
		}
	}

	return EXIT_SUCCESS;
}

void
parse_options (int argc, char *argv[])
{
	// -d depth_value
	// -o (sierpinsky | menger)
	// -m (direct | vertex-buffer | index-buffer)
	// -l (on | off)
	// -w (on | off)
	// -t (on | off)
	// -b (on | off)
	// -s (flat | smooth)
}

int 
main (int argc, char *argv[])
{
	parse_options(argc, argv);

	init_sdl();
	init_opengl();
	init_extensions();
	init_animation();

	print_opengl_properties();

	point ta {{1.0, 1.0, 1.0}};
	point tb {{1.0, -1.0, -1.0}};
	point tc {{-1.0, 1.0, -1.0}};
	point td {{-1.0, -1.0, 1.0}};

	struct tetrahedron t {ta, tb, tc, td};
	std::vector<struct triangle> tv = create_sierpinsky_tetrahedron(t, 8);
	triangles = convert_to_arrayf(tv);
	triangles_size = tv.size();

	return main_loop();
}

