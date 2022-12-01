#ifndef SPACE2_VECTOR3D_H
#define SPACE2_VECTOR3D_H

typedef struct {
    double X;
    double Y;
    double Z;
} Vector3D;

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

const Vector3D zeroVector = {0,0,0};

#endif //SPACE2_VECTOR3D_H
