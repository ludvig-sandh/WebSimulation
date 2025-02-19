#pragma once

struct Vec2 {
    float x, y;

    Vec2() : x(0), y(0) {}
    Vec2(float x, float y) : x(x), y(y) {}

    Vec2 operator+(const Vec2 &other);
    Vec2 operator-(const Vec2 &other);
    void operator+=(const Vec2 &other);
    void operator-=(const Vec2 &other);
};