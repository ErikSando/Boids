#include <iostream>

#include "Vector2.h"

Vector2 Vector2::normalised() {
    return Vector2(x / magnitude(), y / magnitude());
}

void Vector2::normalise() {
    x /= magnitude();
    y /= magnitude();
}

float Vector2::Dot(const Vector2& v1, const Vector2& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

float Vector2::Cross(const Vector2& v1, const Vector2& v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

Vector2& Vector2::operator*=(const float n) {
    x *= n;
    y *= n;
    return *this;
}

Vector2& Vector2::operator/=(const float n) {
    x /= n;
    y /= n;
    return *this;
}

Vector2& Vector2::operator+=(const Vector2& v) {
    x += v.x;
    y += v.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Vector2& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

bool operator==(const Vector2& v1, const Vector2& v2) {
    return (v1.x == v2.x && v1.y == v2.y);
}

bool operator!=(const Vector2& v1, const Vector2& v2) {
    return (v1.x != v2.x || v1.y != v2.y);
}

Vector2 operator*(const Vector2& v1, const Vector2& v2) {
    Vector2 resultant;
    resultant.x = v1.x * v2.x;
    resultant.y = v1.y * v2.y;
    return resultant;
}

Vector2 operator*(const Vector2& v, const float n) {
    Vector2 resultant;
    resultant.x = v.x * n;
    resultant.y = v.y * n;
    return resultant;
}

Vector2 operator*(const float n, const Vector2& v) {
    Vector2 resultant;
    resultant.x = v.x * n;
    resultant.y = v.y * n;
    return resultant;
}

Vector2 operator/(const Vector2& v1, const Vector2& v2) {
    Vector2 resultant;
    resultant.x = v1.x / v2.y;
    resultant.y = v1.y / v2.y;
    return resultant;
}

Vector2 operator/(const Vector2& v, const float n) {
    Vector2 resultant;
    resultant.x = v.x / n;
    resultant.y = v.y / n;
    return resultant;
}

Vector2 operator/(const float n, const Vector2& v) {
    Vector2 resultant;
    resultant.x = n / v.x;
    resultant.y = n / v.y;
    return resultant;
}

Vector2 operator+(const Vector2& v1, const Vector2& v2) {
    Vector2 resultant;
    resultant.x = v1.x + v2.x;
    resultant.y = v1.y + v2.y;
    return resultant;
}

Vector2 operator-(const Vector2& v1, const Vector2& v2) {
    Vector2 resultant;
    resultant.x = v1.x - v2.x;
    resultant.y = v1.y - v2.y;
    return resultant;
}

Vector2 operator-(const Vector2& v) {
    Vector2 resultant;
    resultant.x = -v.x;
    resultant.y = -v.y;
    return resultant;
}