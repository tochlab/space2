#include <stdbool.h>

#include <SDL2/SDL.h>
#include <sys/time.h>

#include "vector3d.h"
#include "Sol.h"

double distance_sys(Vector3D o0, Vector3D o1) {
    Vector3D tmp = {
            o1.X - o0.X,
            o1.Y - o0.Y,
            o1.Z - o0.Z};
    return len(tmp);
}

typedef struct {
    size_t count;
    Vector3D* positions;
    Vector3D* velocities;
    double* massesK;
} SystemObjects;

Vector3D gravity_calculate(SystemObjects *ss, size_t idx0, size_t idx1) {
    const double G = 6.6743E-11;
    if(idx0 == idx1) {
        return zeroVector;
    }

    double dist = distance_sys(ss->positions[idx0],ss->positions[idx1]);
    double F = G * ((ss->massesK[idx0] * ss->massesK[idx1]) / (dist*dist));
    Vector3D result = {0,0,0};
    result.X = (F * (ss->positions[idx1].X - ss->positions[idx0].X)/dist) / ss->massesK[idx0];
    result.Y = (F * (ss->positions[idx1].Y - ss->positions[idx0].Y)/dist) / ss->massesK[idx0];
    result.Z = (F * (ss->positions[idx1].Z - ss->positions[idx0].Z)/dist) / ss->massesK[idx0];
    return result;
}

void dump_sysobject(SystemObjects *ss, size_t idx) {
    printf("%ld: Px %f Py %f Pz %f Vx %f Vy %f Vz %f\n", idx,
              ss->positions[idx].X,
              ss->positions[idx].Y,
              ss->positions[idx].Z,
              ss->velocities[idx].X,
              ss->velocities[idx].Y,
              ss->velocities[idx].Z);
}

static SDL_Renderer* renderer;
SDL_Window *window;

double zoom = 16;

const int WindowWidth = 1280;
const int WindowHeight = 1024;

int64_t time_now_mks() {
    struct timeval time_now = {0,0};
    gettimeofday(&time_now, NULL);
    return time_now.tv_sec * 1000000 + time_now.tv_usec;
}

int64_t elapsed_time_mks(struct timeval a, struct timeval b) {
    int64_t a_mks = a.tv_sec * 1000000 + a.tv_usec;
    int64_t b_mks = b.tv_sec * 1000000 + b.tv_usec;
    return a_mks - b_mks;
}

double get_scale() {
    return AstroUnitM / zoom;
}

void sysobject_draw(Vector3D pos, size_t idx) {
    SDL_RenderDrawPointF(renderer, (pos.X / get_scale()) + (WindowWidth / 2), (pos.Y / get_scale()) + (WindowHeight / 2));
}

bool isRunning = true;

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEWHEEL:
            if(event.wheel.y == -1) {
                zoom /= 2;
            } else {
                zoom *= 2;
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            break;
        default:
            break;
    }
}

void system_update(SystemObjects *ss) {
    for(size_t idx = 0;idx<ss->count;idx++) {
        Vector3D acc_sum = {0, 0, 0};
        for(size_t idx1 = 0;idx1<ss->count;idx1++) {
            acc_sum = add(acc_sum, gravity_calculate(ss, idx, idx1));
        }
        ss->velocities[idx] = add(ss->velocities[idx], acc_sum);
        ss->positions[idx] = add(ss->positions[idx], ss->velocities[idx]);
    }
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
        sysobject_draw(ss->positions[idx], -1);
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

void system_dump(SystemObjects *ss) {
    for(size_t idx = 0;idx < ss->count; idx++) {
        dump_sysobject(ss, idx);
    }
}

//void generate_asteroids(SystemObjects so, int n) {
//    size_t new_size = so.count + n;
//    so.positions.resize(new_size);
//    so.velocities.resize(new_size);
//    so.massesK.resize(new_size);
//    for(size_t i = so.count;i<new_size;i++) {
//        double rnd = (rand()/2147483647.);
//        so.massesK[i] = 0.0017 * EarthMassKg * rnd;
//        so.positions[i] = {Mars.position.X + (Saturn.position.X - Mars.position.X ) * rnd, 0, 0};
//        so.velocities[i] = {0, Mars.velocity.Y + rnd, 0};
//    }
//    so.count = new_size;
//}

void system_add_object(SystemObjects *so, SpaceObject o) {
    so->positions = realloc(so->positions, (so->count+1) * sizeof(Vector3D));
    so->positions[so->count] = o.position;
    so->velocities = realloc(so->velocities, (so->count + 1) * sizeof(Vector3D));
    so->velocities[so->count] = o.velocity;
    so->massesK = realloc(so->massesK, (so->count + 1) * sizeof(Vector3D));
    so->massesK[so->count] = o.massKg;
    so->count++;
}

SystemObjects *system_init() {
    SystemObjects *result = malloc(sizeof(SystemObjects));
    result->count = 0;
    result->positions = NULL;
    result->velocities = NULL;
    result->massesK = NULL;
    return result;
}

void system_free(SystemObjects *so) {
    free(so->positions);
    free(so->velocities);
    free(so->massesK);
    so->count = 0;
    free(so);
    so = NULL;
}

int main() {
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
            i = 0;
            start_time_mks = end_time_mks;
        }
    }
    printf("\nI %d\n", i);

    system_dump(sol);
    system_free(sol);
    return 0;
}
