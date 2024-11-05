#include "Tile.h"
#include <random>

char Tile::GetChar() const
{
    return (char)_type;
}

bool Tile::IsWalkable() const
{
    return _type != Type::Wall;
}

bool Tile::IsFinish() const
{
    return _type == Type::Finish;
}

Tile Tile::GenerateRandomTile(int wallsFrequencyPercents)
{
    bool isWall = std::rand() % 100 < wallsFrequencyPercents;
    return isWall ? Tile(Type::Wall) : Tile(Type::Floor);
}
