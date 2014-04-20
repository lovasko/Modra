#include "opengl_properties.h"
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

void
init_opengl ()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(20.0f);
}

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

  SDL_Surface *surface = SDL_SetVideoMode(600, 600, 32, 
	    SDL_OPENGL | SDL_GL_DOUBLEBUFFER);

  if (!surface)
  {
    fprintf(stderr, "Video mode set failed: %s", SDL_GetError());
    quit(1);
  }
}

void
init_extensions ()
{
	bool vbo_capable = false;

  GLenum err = glewInit();
  if (err != GLEW_OK)
  {
    printf("GLEW initialization error: %s\n", glewGetErrorString(err));
    return;
  }

  vbo_capable = GL_ARB_vertex_buffer_object;
}

int 
main (int argc, char *argv[])
{
	init_sdl();
	print_opengl_properties();
	quit(0);
}
