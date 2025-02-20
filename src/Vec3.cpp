#include "Vec3.h"

Vec3 Vec3::operator+(const Vec3 &other) {
    Vec3 newPoint;
    newPoint.x = x + other.x;
    newPoint.y = y + other.y;
    newPoint.z = z + other.z;
    return newPoint;
}

Vec3 Vec3::operator-(const Vec3 &other) {
    Vec3 newPoint;
    newPoint.x = x - other.x;
    newPoint.y = y - other.y;
    newPoint.z = z - other.z;
    return newPoint;
}

void Vec3::operator+=(const Vec3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
}

void Vec3::operator-=(const Vec3 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
}

Vec3 Vec3::operator*(const float &scalar) {
    return Vec3(x * scalar, y * scalar, z * scalar);
}

void Vec3::operator*=(const float &scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
}