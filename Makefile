CC=g++

CFLAGS = -Wall -Wextra
LIBS=libs/ONEGIN_files.o libs/ONEGIN_strings.o libs/ONEGIN_structs.o libs/barmaley.o -lSDL2_image -g `sdl2-config --cflags --libs`


barmaley_o: include/barmaley.hpp src/barmaley.cpp
	$(CC) $(CFLAGS) -c src/barmaley.cpp -o libs/barmaley.o

patch:barmaley_o src/patch.cpp
	$(CC) src/patch.cpp $(LIBS) $(CFLAGS) -o bin/patch
