CFLAGS = -Wall -Wextra -std=c11 -pedantic -ggdb -fPIC `pkg-config --cflags sdl2 SDL2_image`
LIBS = `pkg-config --libs sdl2 SDL2_image` -lm

all: floatimg

libfloatimg.a: libfloatimg.o
	ar rcs libfloatimg.a libfloatimg.o

libfloatimg.o: libfloatimg.c
	$(CC) $(CFLAGS) -o libfloatimg.o -c libfloatimg.c $(LIBS)

floatimg: floatimg.o libfloatimg.a
	$(CC) $(CFLAGS) -o floatimg floatimg.o libfloatimg.a $(LIBS)

floatimg.o: floatimg.c
	$(CC) $(CFLAGS) -c floatimg.c $(LIBS)
