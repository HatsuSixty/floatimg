CFLAGS = -Wall -Wextra -std=c11 -pedantic -ggdb `pkg-config --cflags sdl2 SDL2_image`
LIBS = `pkg-config --libs sdl2 SDL2_image` -lm

floatimg: main.o
	$(CC) $(CFLAGS) -o floatimg main.o $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LIBS)
