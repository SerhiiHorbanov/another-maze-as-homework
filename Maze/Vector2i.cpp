#include "Vector2i.h"

std::string Vector2i::ToString() const
{
    return "{ " + std::to_string(x) + ", " + std::to_string(y) + " }";
}

Vector2i operator+(const Vector2i left, const Vector2i right)
{
    return Vector2i(left.x + right.x, left.y + right.y);
}