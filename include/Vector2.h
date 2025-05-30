#pragma once

#include <cmath>
#include <iostream>

class Vector2 {
    public:
    
    float x, y;

    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float n) : x(n), y(n) {}
    Vector2(float x, float y) : x(x), y(y) {}

    inline float magnitude() const { return sqrt(x * x + y * y); }

    Vector2 normalised();
    void normalise();

    static float Dot(const Vector2& v1, const Vector2& v2);
    static float Cross(const Vector2& v1, const Vector2& v2);
    static float AngleBetween(const Vector2& v1, const Vector2& v2);

    static Vector2 FromAngle(const float angle);

    Vector2& operator*=(const float n);
    Vector2& operator/=(const float n);
    Vector2& operator+=(const Vector2& v);
    Vector2& operator-=(const Vector2& v);

    static Vector2 Zero() { return Vector2(0.0, 0.0); }
    static Vector2 One() { return Vector2(1.0, 1.0); }
    static Vector2 Left() { return Vector2(-1.0, 0.0); }
    static Vector2 Right() { return Vector2(1.0, 0.0); }
    static Vector2 Up() { return Vector2(0.0, -1.0); }
    static Vector2 Down() { return Vector2(0.0, 1.0); }
};

std::ostream& operator<<(std::ostream& os, const Vector2& v);

bool operator==(const Vector2& v1, const Vector2& v2);
bool operator!=(const Vector2& v1, const Vector2& v2);

Vector2 operator*(const Vector2& v1, const Vector2& v2);
Vector2 operator*(const Vector2& v, const float n);
Vector2 operator*(const float n, const Vector2& v);
Vector2 operator/(const Vector2& v1, const Vector2& v2);
Vector2 operator/(const Vector2& v, const float n);
Vector2 operator/(const float n, const Vector2& v);
Vector2 operator+(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v);