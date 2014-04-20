clang++ -DTEST_FLOAT -o testf -std=c++11 main.cpp sierpinsky_tetrahedron.cpp utilities.cpp fractal_helpers.cpp menger_sponge.cpp options.cpp stats.cpp -I/opt/local/include -L/opt/local/lib -lGLEW -lSDL -lSDLmain -framework OpenGL -framework Cocoa

clang++ -DTEST_DOUBLE -o testd -std=c++11 main.cpp sierpinsky_tetrahedron.cpp utilities.cpp fractal_helpers.cpp menger_sponge.cpp options.cpp stats.cpp -I/opt/local/include -L/opt/local/lib -lGLEW -lSDL -lSDLmain -framework OpenGL -framework Cocoa

clang++ -o info -std=c++11 info_main.cpp opengl_properties.cpp -I/opt/local/include -L/opt/local/lib -lGLEW -lSDL -lSDLmain -framework OpenGL -framework Cocoa

