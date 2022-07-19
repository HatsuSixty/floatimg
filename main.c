#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void scc(int code) {
    if (code < 0) {
        fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
    }
}

int main(int argc, const char** argv) {
    assert((argc > 1) && "Image not provided");

    scc(SDL_Init(SDL_INIT_EVERYTHING));
    scc(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP));

    int width;
    int height;
    {
        int n;
        unsigned char *image_data = stbi_load(argv[1], &width, &height, &n, 0);
        stbi_image_free(image_data);
        if (image_data == NULL) {
            fprintf(stderr, "ERROR: Invalid image\n");
            exit(1);
        }
    }

    SDL_Window* window = SDL_CreateShapedWindow(argv[1],
                                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                                width, height, SDL_WINDOW_BORDERLESS);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    SDL_Surface* image = IMG_Load(argv[1]);
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
