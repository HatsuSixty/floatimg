#ifndef LIBFLOATIMG_H
#define LIBFLOATIMG_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void floatimg(const char* file_path);

#endif // LIBFLOATIMG_H
