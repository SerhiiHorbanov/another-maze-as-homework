#include "Tile.h"

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
