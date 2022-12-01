#include "renderer.h"

#include <SDL2/SDL.h>
#include "utils.h"

static SDL_Renderer* renderer;
SDL_Window *window;

const int WindowWidth = 1280;
const int WindowHeight = 1024;
static double zoom = 16;

double get_zoom() {
    return zoom;
}

double get_scale() {
    return AstroUnitM / zoom;
}

void zoom_inc() {
    zoom /= 2;
}

void zoom_dec() {
    zoom *= 2;
}

void sysobject_draw(Vector3D pos) {
    SDL_RenderDrawPointF(renderer, (pos.X / get_scale()) + (WindowWidth / 2), (pos.Y / get_scale()) + (WindowHeight / 2));
}

void render_clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

int64_t prev_render_time = 0;

void system_render(SystemObjects *ss) {
    int64_t now_time = time_now_mks();
    if(now_time - prev_render_time < 16000) {
        return;
    }
    prev_render_time = now_time;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPointF(renderer, WindowWidth/2., WindowHeight/2.);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    for(size_t idx = 0;idx<ss->count;idx++) {
        sysobject_draw(ss->positions[idx]);
    }

    SDL_RenderPresent(renderer);
}

int render_init() {
    int flags = SDL_WINDOW_SHOWN;

    int err = SDL_Init(SDL_INIT_EVERYTHING);
    if (err != 0) {
        SDL_GetError();
        fprintf(stderr,"SDL_Init error '%s'\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Space", 0, 0, WindowWidth, WindowHeight, flags);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow error!\n");
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer error!\n");
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    return 0;
}

