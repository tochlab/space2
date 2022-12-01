#ifndef SPACE2_STARSYSTEM_H
#define SPACE2_STARSYSTEM_H

#include <stdlib.h>
#include "vector3d.h"
#include "Sol.h"

typedef struct {
    size_t count;
    Vector3D* positions;
    Vector3D* velocities;
    double* massesK;
} SystemObjects;

SystemObjects *system_init();
void system_add_object(SystemObjects *so, SpaceObject o);
void system_dump(SystemObjects *ss);
void system_update(SystemObjects *ss);
void system_free(SystemObjects *so);

#endif //SPACE2_STARSYSTEM_H
