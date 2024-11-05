#include <random>
#include "Player.h"
#include "MazeMap.h"

Player Player::GetRandomlyPlacedPlayer(Vector2i mapSize)
{
    int x = std::rand() % mapSize.x;
    int y = std::rand() % mapSize.y;

    return Player(Vector2i(x, y));
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