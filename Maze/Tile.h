#pragma once

class Tile
{
private:
    enum class Type : char
    {
        Floor = '.',
        Wall = '#',
        Finish = 'F'
    };

    Type _type;

public:
    char GetChar() const;
    bool IsWalkable() const;
    bool IsFinish() const;
};

