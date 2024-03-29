#include <stdbool.h>

#include <SDL2/SDL.h>

#include "utils.h"
#include "Sol.h"
#include "starsystem.h"
#include "renderer.h"

bool isRunning = true;

void process_input() {
    SDL_Event event;
    if(!SDL_PollEvent(&event)) {
        return;
    }
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEWHEEL:
            if(event.wheel.y == -1) {
                zoom_inc();
            } else {
                zoom_dec();
            }
            render_clear();
            break;
        default:
            break;
    }
}

int main() {
    SpaceObject solarSystem[] = {
            Sun, Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptunus, Pluto
    };

    if(render_init() != 0) {
        return EXIT_FAILURE;
    }

    SystemObjects *sol = system_init();

    for(int i = 0;i<10;i++) {
        system_add_object(sol, solarSystem[i]);
    }

    system_dump(sol);

    int i = 0;
    int64_t start_time_mks = 0;
    int64_t end_time_mks = 0;
    start_time_mks = time_now_mks();

    size_t total_iters = 0;
    while(isRunning) {
        process_input();
        system_update(sol);
        system_render(sol);

        i++;
        total_iters++;
        if(i % 100000 == 0) {
            end_time_mks = time_now_mks();
            int64_t time_mks = end_time_mks - start_time_mks;
            printf("%ld Avgitertime %ld mks\n", total_iters, time_mks/i);
            printf("scale %f zoom %f\n", get_scale(), get_zoom());
            i = 0;
            start_time_mks = end_time_mks;
        }
    }
    printf("\nI %d\n", i);

    system_dump(sol);
    system_free(sol);
    return 0;
}
