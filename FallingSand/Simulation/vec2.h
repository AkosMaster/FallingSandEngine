#pragma once
#include <cmath>

struct vec2 {
    float x, y;

    vec2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    // Addition
    vec2 operator+(const vec2& other) const {
        return vec2(x + other.x, y + other.y);
    }

    // Subtraction
    vec2 operator-(const vec2& other) const {
        return vec2(x - other.x, y - other.y);
    }

    // Compound addition
    vec2& operator+=(const vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // Compound subtraction
    vec2& operator-=(const vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    // Scalar multiplication
    vec2 operator*(float scalar) const {
        return vec2(x * scalar, y * scalar);
    }

    // Scalar division
    vec2 operator/(float scalar) const {
        return vec2(x / scalar, y / scalar);
    }

    // Compound scalar multiplication
    vec2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // Compound scalar division
    vec2& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // Length (magnitude)
    float length() const {
        return std::sqrt(x * x + y * y);
    }

    // Normalize vector
    vec2 normalized() const {
        float len = length();
        if (len == 0.0f) return vec2(0.0f, 0.0f);
        return vec2(x / len, y / len);
    }

    // Dot product
    float dot(const vec2& other) const {
        return x * other.x + y * other.y;
    }
};