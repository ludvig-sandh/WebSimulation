#include <cmath>
#include "Vec2.h"

Vec2 Vec2::operator+(const Vec2 &other) const {
    Vec2 newPoint;
    newPoint.x = x + other.x;
    newPoint.y = y + other.y;
    return newPoint;
}

Vec2 Vec2::operator-(const Vec2 &other) const {
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

Vec2 Vec2::operator*(const float &scalar) const {
    return Vec2(x * scalar, y * scalar);
}

void Vec2::operator*=(const float &scalar) {
    x *= scalar;
    y *= scalar;
}

bool Vec2::operator<(const Vec2 &other) const {
    if (x == other.x) {
        return y < other.y;
    }
    return x < other.x;
}

bool Vec2::operator<=(const Vec2 &other) const {
    if (x == other.x) {
        return y <= other.y;
    }
    return x <= other.x;
}

bool Vec2::operator>(const Vec2 &other) const {
    if (x == other.x) {
        return y > other.y;
    }
    return x > other.x;
}

bool Vec2::operator>=(const Vec2 &other) const {
    if (x == other.x) {
        return y >= other.y;
    }
    return x >= other.x;
}

bool Vec2::operator==(const Vec2 &other) const {
    return (x == other.x && y == other.y);
}

bool Vec2::operator!=(const Vec2 &other) const {
    return (x != other.x || y != other.y);
}

float Vec2::abs() const {
    return sqrtf(x * x + y * y);
}