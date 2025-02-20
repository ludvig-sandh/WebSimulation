#pragma once

struct Vec3 {
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3 &other);
    Vec3 operator-(const Vec3 &other);
    void operator+=(const Vec3 &other);
    void operator-=(const Vec3 &other);

    Vec3 operator*(const float &scalar);
    void operator*=(const float &scalar);
};