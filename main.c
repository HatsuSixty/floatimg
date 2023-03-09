#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void scc(int code) {
    if (code < 0) {
        fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
    }
}

void usage(FILE* stream, const char* program_name) {
    fprintf(stream, "Usage: %s [FLAGS] <IMAGE>\n", program_name);
    fprintf(stream, "  FLAGS:\n");
    fprintf(stream, "    --help | -h          Show this help and exit with 0 code\n");
    fprintf(stream, "  IMAGE:\n");
    fprintf(stream, "    The image that is going to be displayed\n");
}

int ends_with(const char *str, const char *suffix)
{
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

int main(int argc, const char** argv) {
    if (argc < 2) {
        fprintf(stderr, "ERROR: Not enough arguments were provided\n");
        usage(stderr, argv[0]);
        exit(1);
    }

    const char* file_path;

    for (int i = 1; i < argc; ++i) {
        if ((strcmp(argv[i], "--help") == 0) || (strcmp(argv[i], "--h") == 0)) {
            usage(stdout, argv[0]);
            exit(0);
        } else {
            file_path = argv[i];
        }
    }

    if (!(ends_with(file_path, ".jpg")  ||
          ends_with(file_path, ".jpeg") ||
          ends_with(file_path, ".png")  ||
          ends_with(file_path, ".tif")  ||
          ends_with(file_path, ".tiff") ||
          ends_with(file_path, ".webp")))
    {
        fprintf(stderr, "ERROR: Invalid image format\n");
        exit(1);
    }

    int width;
    int height;
    {
        int n;
        unsigned char *image_data = stbi_load(file_path, &width, &height, &n, 0);
        stbi_image_free(image_data);
        if (image_data == NULL) {
            fprintf(stderr, "ERROR: Invalid image\n");
            exit(1);
        }
    }

    scc(SDL_Init(SDL_INIT_EVERYTHING));
    scc(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP));

    SDL_Window* window = SDL_CreateShapedWindow(file_path,
                                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                                width, height, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_Surface* image = IMG_Load(file_path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_SetWindowShape(window, image, 0);

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        SDL_WaitEvent(&event);

        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        }

        scc(SDL_RenderCopy(renderer, texture, NULL, NULL));
        SDL_RenderPresent(renderer);
        scc(SDL_RenderClear(renderer));
    }

    SDL_Quit();
    IMG_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    return 0;
}
