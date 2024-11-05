#pragma once
#include <string>
#include "Vector2i.h"

class Input
{
private:
    char lastInput;
    Vector2i walkDirection;

public:
    void GetInput();
    void ProcessInput();

    Vector2i GetWalkDirection() const;
};

