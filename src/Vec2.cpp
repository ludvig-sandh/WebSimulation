#include "Vec2.h"

Vec2 Vec2::operator+(const Vec2 &other) {
    Vec2 newPoint;
    newPoint.x = x + other.x;
    newPoint.y = y + other.y;
    return newPoint;
}

Vec2 Vec2::operator-(const Vec2 &other) {
    Vec2 newPoint;
    newPoint.x = x - other.x;
    newPoint.y = y - other.y;
    return newPoint;
}

void Vec2::operator+=(const Vec2 &other) {
    x += other.x;
    y += other.y;
}

void Vec2::operator-=(const Vec2 &other) {
    x -= other.x;
    y -= other.y;
}

Vec2 Vec2::operator*(const float &scalar) {
    return Vec2(x * scalar, y * scalar);
}

void Vec2::operator*=(const float &scalar) {
    x *= scalar;
    y *= scalar;
}