#include "starsystem.h"
#include "Sol.h"

#include <stdio.h>

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

void system_dump(SystemObjects *ss) {
    for(size_t idx = 0;idx < ss->count; idx++) {
        dump_sysobject(ss, idx);
    }
}

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
