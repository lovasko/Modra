#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "options.h"

void
parse_options (int argc, char *argv[])
{
	int option;	

	while ((option = getopt(argc, argv, "d:o:m:l:w:t:b:s:")) != -1)
	{
		switch(option)
		{
		// TODO use strtol
		case 'd': 
			fractal_depth = atoi(optarg);
		break;

		case 'o': 
			if (strcmp("sierpinsky", optarg) == 0)
				fractal = SIERPINSKY_TETRAHEDRON;
			else if (strcmp("menger", optarg) == 0)
				fractal = MENGER_SPONGE;
			else
			{
				fprintf(stderr, "unsupported object name\n");
				exit(1);
			}
		break;

		case 'm': 
			if (strcmp("immediate", optarg) == 0)
				drawing = IMMEDIATE;
			else if (strcmp("vertex-buffer", optarg) == 0)
				drawing = VERTEX_BUFFER;
			else if (strcmp("index-buffer", optarg) == 0)
				drawing = INDEX_BUFFER;
			else
			{
				fprintf(stderr, "unsupported drawing method\n");
				exit(1);
			}
		break;

		case 's': 
			if (strcmp("flat", optarg) == 0)
				shading = FLAT;
			else if (strcmp("smooth", optarg) == 0)
				shading = SMOOTH;
			else
			{
				fprintf(stderr, "unsupported shading method\n");
				exit(1);
			}
		break;

		case 'f': 
			if (strcmp("single", optarg) == 0)
				floating_numbers = SINGLE;
			else if (strcmp("double", optarg) == 0)
				floating_numbers = DOUBLE;
			else
			{
				fprintf(stderr, "unsupported floating numbers format\n");
				exit(1);
			}
		break;

		case 'b': 
			if (strcmp("on", optarg) == 0)
				blending_flag = true;
			else if (strcmp("off", optarg) == 0)
				blending_flag = false;
			else
			{
				fprintf(stderr, "unsupported blending state\n");
				exit(1);
			}
		break;

		case 't': 
			if (strcmp("on", optarg) == 0)
				texture_flag = true;
			else if (strcmp("off", optarg) == 0)
				texture_flag = false;
			else
			{
				fprintf(stderr, "unsupported texturing state\n");
				exit(1);
			}
		break;

		case 'l': 
			if (strcmp("on", optarg) == 0)
				light_flag = true;
			else if (strcmp("off", optarg) == 0)
				light_flag = false;
			else
			{
				fprintf(stderr, "unsupported lighting state\n");
				exit(1);
			}
		break;

		case 'w': 
			if (strcmp("on", optarg) == 0)
				wireframe_flag = true;
			else if (strcmp("off", optarg) == 0)
				wireframe_flag = false;
			else
			{
				fprintf(stderr, "unsupported wireframe state\n");
				exit(1);
			}
		break;

		case '?':
			fprintf(stderr, "invalid option -- '%c'\n", optopt);
			exit(1);
		return;

		default:
			exit(1);
		}
	}
}

