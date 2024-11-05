#pragma once
#include "Input.h"
#include "Player.h"
#include "Tile.h"
#include "Vector2i.h"

class MazeMap
{
private:
    Vector2i _size;
    Tile* _tiles;
    Player _player;

    std::string GetImage();

    MazeMap(const Vector2i& _size, Tile* _tiles, const Player& _player) : 
        _size(_size), 
        _tiles(_tiles), 
        _player(_player)
    {}

public:
    static MazeMap GenerateNewMap();
    void GenerateWalls(int wallsFrequencyPercents);
    void PlaceFinish();

    bool IsInBounds(Vector2i position) const;
    const Tile* GetTile(Vector2i position) const;

    bool IsGameEnded();

    void Update(const Input& input);

    void Render();
};