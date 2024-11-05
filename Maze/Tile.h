#pragma once

class Tile
{
public:
    enum class Type : char
    {
        Floor = '.',
        Wall = '#',
        Finish = 'F'
    };

private:
    Type _type;

public:

    Tile(Type type) :
        _type(type)
    {}

    Tile() :
        _type(Type::Floor)
    {}

    char GetChar() const;
    bool IsWalkable() const;
    bool IsFinish() const;

    static Tile GenerateRandomTile(int wallsFrequencyPercents);
};

