#pragma once
#include "Vector2i.h"
#include "MazeMap.h"
#include "Input.h"

class MazeGame
{
private:
    MazeMap _map = MazeMap::GenerateNewMap();
    Input _input;

    void SetRandomSeed();
public:

    void Run();

    void Render();
    void Input();
    void Update();
};

