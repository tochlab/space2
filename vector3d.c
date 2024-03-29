#include <math.h>
#include "vector3d.h"

Vector3D add(Vector3D v0, Vector3D v1) {
    v0.X += v1.X;
    v0.Y += v1.Y;
    v0.Z += v1.Z;
    return v0;
}

Vector3D sub(Vector3D v0, Vector3D v1) {
    v0.X -= v1.X;
    v0.Y -= v1.Y;
    v0.Z -= v1.Z;
    return v0;
}

double len(Vector3D v) {
    double result = sqrt((v.X*v.X) + (v.Y*v.Y) + (v.Z*v.Z));
    return result;
}

double distance_sys(Vector3D o0, Vector3D o1) {
    Vector3D tmp = {
            o1.X - o0.X,
            o1.Y - o0.Y,
            o1.Z - o0.Z};
    return len(tmp);
}

