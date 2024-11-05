#include "MazeMap.h"
#include <iostream>

const Tile* MazeMap::GetTile(Vector2i position) const
{
    if (IsInBounds(position))
    {
        const int index = (position.y * _size.x) + position.x;
        return _tiles + index;
    }
    return nullptr;
}

void MazeMap::GenerateWalls(int wallsFrequencyPercents)
{
    int tilesAmount = _size.x * _size.y;
    for (int i = 0; i < tilesAmount; i++)
    {
        _tiles[i] = Tile::GenerateRandomTile(wallsFrequencyPercents);
    }
}

void MazeMap::PlaceFinish()
{
    const int x = std::rand() % _size.x;
    const int y = std::rand() % _size.y;

    const int index = y * _size.x + x;
    _tiles[index] = Tile(Tile::Type::Finish);
}

bool MazeMap::IsInBounds(Vector2i position) const
{
    bool FitsWithMin = position.x >= 0 && position.y >= 0;
    bool fitsWithMax = position.x < _size.x && position.y < _size.y;
    return FitsWithMin && fitsWithMax;
}

MazeMap MazeMap::GenerateNewMap()
{
    Vector2i size = Vector2i(10, 10);
    Tile* tiles = new Tile[size.y * size.x];
    Player player = Player::GetRandomlyPlacedPlayer(size);

    MazeMap result = MazeMap(size, tiles, player);
    result.GenerateWalls(25);
    result.PlaceFinish();

    return result;
}

bool MazeMap::IsGameEnded()
{
    return GetTile(_player.GetPosition())->IsFinish();
}

void MazeMap::Update(const Input& input)
{
    _player.Walk(*this, input.GetWalkDirection());
}

void MazeMap::Render()
{
    std::cout << GetImage();
}

std::string MazeMap::GetImage()
{
    std::string result = std::string(_size.x * (_size.y + 1), '\n');

    for (int y = 0; y < _size.y; y++)
    {
        for (int x = 0; x < _size.x; x++)
        {
            const int index = (_size.y + 1) * y + x;
            result[index] = GetTile({x, y})->GetChar();
        }
    }

    const int playerCharIndex = (_size.y + 1) * _player.GetPosition().y + _player.GetPosition().x;
    result[playerCharIndex] = Player::character;

    return result;
}