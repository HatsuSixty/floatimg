CFLAGS = -Wall -Wextra -std=c11 -pedantic -ggdb -fPIC `pkg-config --cflags sdl2 SDL2_image`
LIBS = `pkg-config --libs sdl2 SDL2_image` -lm

all: floatimg

libfloatimg.so: libfloatimg.o
	$(CC) $(CFLAGS) -shared -o libfloatimg.so libfloatimg.o $(LIBS)

libfloatimg.o: libfloatimg.c
	$(CC) $(CFLAGS) -o libfloatimg.o -c libfloatimg.c $(LIBS)

floatimg: main.o libfloatimg.so
	$(CC) $(CFLAGS) -o floatimg main.o libfloatimg.so $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LIBS)
