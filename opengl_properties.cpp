#include <OpenGL/gl.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "opengl_properties.h"

const char*
maybe (char *string)
{
	return (string ? string : "N/A");
}

void
print_extensions (const char *extensions)
{
	size_t len = strlen(extensions);
			
	printf("\n\t");
	for (unsigned int i = 0; i < len; i++)
	{
		char c = extensions[i];

		if (isspace(c))
		{
			printf("\n");

			if (i != len-1)
			{
				printf("\t");
			}
		}
		else
		{
			printf("%c", c);
		}
	}
}

void
print_opengl_properties ()
{
	char *version = (char*)glGetString(GL_VERSION);
	char *vendor = (char*)glGetString(GL_VENDOR);
	char *renderer = (char*)glGetString(GL_RENDERER);
	char *glsl_version = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
  char *extensions = (char*)glGetString(GL_EXTENSIONS);

  int max_vertices, max_indices;
  glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &max_vertices);
  glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &max_indices);
	
	printf("OpenGL Information\n");
	printf("     Version: %s\n", maybe(version));
	printf("      Vendor: %s\n", maybe(vendor));
	printf("    Renderer: %s\n", maybe(renderer));
	printf("GLSL Version: %s\n", maybe(glsl_version));
	printf("  Extensions:");
	print_extensions(maybe(extensions));
}
