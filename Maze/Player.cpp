#include <random>
#include "Player.h"
#include "MazeMap.h"

Player Player::GetRandomlyPlacedPlayer(Vector2i mapSize)
{
    Vector2i position = Vector2i::GetRandomVector() % mapSize;
    return Player(position);
}

void Player::Walk(const MazeMap& map, const Vector2i delta)
{
    const Vector2i newPosition = _position + delta;

    if (map.IsInBounds(newPosition))
    {
        if (map.GetTile(newPosition)->IsWalkable())
        {
            _position = newPosition;
        }
    }
}

Vector2i Player::GetPosition()
{
    return _position;
}