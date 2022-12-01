#ifndef SPACE2_VECTOR3D_H
#define SPACE2_VECTOR3D_H

typedef struct {
    double X;
    double Y;
    double Z;
} Vector3D;

static const Vector3D zeroVector = {0,0,0};

Vector3D add(Vector3D v0, Vector3D v1);
Vector3D sub(Vector3D v0, Vector3D v1);
double len(Vector3D v);
double distance_sys(Vector3D o0, Vector3D o1);

#endif //SPACE2_VECTOR3D_H
