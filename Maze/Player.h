#pragma once
#include <string>
#include "Input.h"

class MazeMap;

class Player
{
private:
    Vector2i _position;

    Player(const Vector2i& position) : 
        _position(position)
    {}

public:
    static Player GetRandomlyPlacedPlayer(Vector2i mapSize);

    const static char character = '@';

    void Walk(const MazeMap& map, const Vector2i direction);

    Vector2i GetPosition();
};