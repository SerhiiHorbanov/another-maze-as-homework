#include "Vector2i.h"

std::string Vector2i::ToString() const
{
    return "{ " + std::to_string(x) + ", " + std::to_string(y) + " }";
}