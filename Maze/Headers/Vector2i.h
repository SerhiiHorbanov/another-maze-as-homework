#pragma once
#include <string>

struct Vector2i
{
public:
    int x = 0;
    int y = 0;

    Vector2i() :
        x(0),
        y(0)
    {}

    Vector2i(int X, int Y) :
        x(X),
        y(Y)
    {}
};

Vector2i operator+(const Vector2i left, const Vector2i right)
{
    return Vector2i(left.x + right.x, left.y + right.y);
}

Vector2i operator*(const Vector2i left, const int right)
{
    return Vector2i(left.x * right, left.y * right);
}

void operator+=(Vector2i& left, const Vector2i right)
{
    left = left + right;
}