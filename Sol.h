#ifndef SPACE_SOL_H
#define SPACE_SOL_H

#include <stdint.h>
#include "vector3d.h"

typedef uint64_t object_id;

typedef struct {
    object_id id;
    Vector3D position;
    Vector3D velocity;
    Vector3D accel;
    double massKg;
} SpaceObject;

static const double AstroUnitM = 149597870700;
static const double EarthMassKg = 5.974E24;

//static SpaceObject Body = {
//        1, {6378.1 * 1000, 0, 0}, {0, 0, 0}, {0, 0, 0},
//        1
//};

static const SpaceObject Sun = {
        0, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 1.98892E30
};

static const SpaceObject Mercury = {
        1, {0.4 * AstroUnitM, 0, 0}, {0, 47360, 0}, {0, 0, 0}, 0.055 * EarthMassKg
};

static const SpaceObject Venus = {
        2, {0.723332 * AstroUnitM, 0, 0}, {0, 35020, 0}, {}, 0.815 * EarthMassKg
};

static const SpaceObject Earth = {
        3, {AstroUnitM, 0, 0}, {0, 29780, 0}, {0, 0, 0}, 1 * EarthMassKg
};

static const SpaceObject Mars = {
        4, {1.523662 * AstroUnitM, 0, 0}, {0, 24130, 0}, {}, 0.107 * EarthMassKg
};

static const SpaceObject Jupiter = {
        5, {5.204267 * AstroUnitM, 0, 0}, {0, 13070, 0}, {}, 317.8 * EarthMassKg
};

static const SpaceObject Saturn = {
        6, {9.53667594 * AstroUnitM, 0, 0}, {0, 9690, 0}, {}, 95.2 * EarthMassKg
};

static const SpaceObject Uranus = {
        7, {19.18916464 * AstroUnitM, 0, 0}, {0, 6810, 0}, {}, 14.37 * EarthMassKg
};

static const SpaceObject Neptunus = {
        8, {30.06992276 * AstroUnitM, 0, 0}, {0, 5430, 0}, {}, 17.15 * EarthMassKg
};

static const SpaceObject Pluto = {
        9, {39.48211675 * AstroUnitM, 0, 0}, {0, 4660, 0}, {}, 0.002 * EarthMassKg
};

#endif //SPACE_SOL_H
