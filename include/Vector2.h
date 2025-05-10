#pragma once

#include <cmath>
#include <iostream>

class Vector2 {
    public:
    
    float x, y;

    Vector2() : x(0.0), y(0.0) {}
    Vector2(float x, float y) : x(x), y(y) {}

    inline float magnitude() { return sqrt(x * x + y * y); }

    Vector2 normalised();

    static float Dot(const Vector2& v1, const Vector2& v2);
    static float Cross(const Vector2& v1, const Vector2& v2);

    Vector2& operator*=(const float n);
    Vector2& operator/=(const float n);
    Vector2& operator+=(const Vector2& v);
    Vector2& operator-=(const Vector2& v);

    static Vector2 Zero() { return Vector2(0, 0); }
    static Vector2 One() { return Vector2(1, 1); }
    static Vector2 Left() { return Vector2(-1, 0); }
    static Vector2 Right() { return Vector2(1, 0); }
    static Vector2 Up() { return Vector2(0, -1); }
    static Vector2 Down() { return Vector2(0, 1); }
};

std::ostream& operator<<(std::ostream& os, const Vector2& v);

bool operator==(const Vector2& v1, const Vector2& v2);
bool operator!=(const Vector2& v1, const Vector2& v2);

Vector2 operator*(const float n, const Vector2& v);
Vector2 operator*(const Vector2& v, const float n);
Vector2 operator/(const Vector2& v, const float n);
Vector2 operator+(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v);