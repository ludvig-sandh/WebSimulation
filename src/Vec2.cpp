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