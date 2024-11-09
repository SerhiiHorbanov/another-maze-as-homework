#include <conio.h>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>
#include "Vector2i.h"

const int width = 10;
const int height = 10;
const int wallsFrequencyPercents = 25;
const int spikesFrequencyPercents = 10;

const int spikesPlusWallsFrequencyPercents = wallsFrequencyPercents + spikesFrequencyPercents;

enum class TileType : char
{
    Wall = '#',
    Floor = '.',
    Finish = 'F',
    Jetpack = 'J',
    Spike = '^'
};
const char playerChar = '@';

TileType map[height][width];
int timeLeft = 20;

Vector2i playerPosition;

bool playerHasJetpack = false;

Vector2i direction;

Vector2i delta;

TileType GetMapTile(Vector2i position)
{
    return map[position.y][position.x];
}
TileType GetMapTile(int x, int y)
{
    return map[y][x];
}
void SetMapTile(Vector2i position, TileType tile)
{
    map[position.y][position.x] = tile;
}
Vector2i GetRandomMapPosition()
{
    int x = std::rand() % width;
    int y = std::rand() % height;

    return { x, y };
}

TileType GenerateTile()
{
    int random = std::rand() % 100;

    if (random < wallsFrequencyPercents)
        return TileType::Wall;
    if (random < spikesPlusWallsFrequencyPercents)
        return TileType::Spike;
    
    return TileType::Floor;
}
void ReplaceRandomTileOfTypeWith(TileType newTile, TileType replaced)
{
    std::vector<TileType*> possibleReplcedTilesPositions = std::vector<TileType*>();
    possibleReplcedTilesPositions.reserve(width * height);

    
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (map[y][x] == replaced)
                possibleReplcedTilesPositions.push_back(&map[y][x]);
        }
    }

    const int possibleReplcedTilesPositionsAmount = possibleReplcedTilesPositions.size();
    if (possibleReplcedTilesPositionsAmount == 0)
        return;

    const int randomIndex = std::rand() % possibleReplcedTilesPositionsAmount;
    *possibleReplcedTilesPositions[randomIndex] = newTile;
}
void GenerateMap()
{
    srand(time(NULL));

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            map[y][x] = GenerateTile();
        }
    }
    ReplaceRandomTileOfTypeWith(TileType::Finish, TileType::Floor);
    ReplaceRandomTileOfTypeWith(TileType::Jetpack, TileType::Floor);
}

void RandomizePlayerPosition()
{
    Vector2i newPosition = GetRandomMapPosition();
    playerPosition = newPosition;
}

bool IsWalkable(TileType tile)
{
    return tile != TileType::Wall && !(playerHasJetpack && tile == TileType::Jetpack);
}
bool CanFlyOver(TileType tile)
{
    return tile == TileType::Wall || tile == TileType::Jetpack;
}
bool isInMapBounds(int x, int y)
{
    bool notTooLow = x >= 0 && y >= 0;
    bool notTooHigh = x >= 0 && y >= 0;
    return notTooLow && notTooHigh;
}
bool isInMapBounds(Vector2i position)
{
    return isInMapBounds(position.x, position.y);
}
bool CanWalk()
{
    Vector2i toPosition = playerPosition + direction;
    if (!isInMapBounds(toPosition))
        return false;
    return IsWalkable(GetMapTile(toPosition));
}
bool CanUseJetpack()
{
    if (!playerHasJetpack)
        return false;

    Vector2i flyingOverPosition = playerPosition + direction;
    Vector2i toPosition = playerPosition + (direction * 2);

    if (!isInMapBounds(toPosition))
        return false;

    TileType toTile = GetMapTile(toPosition);
    TileType flyingOverTile = GetMapTile(flyingOverPosition);

    if (CanFlyOver(GetMapTile(flyingOverPosition)))
        return IsWalkable(toTile);
}

void UpdateMovingDeltas()
{
    if (CanWalk())
    {
        delta = direction;
        return;
    }
    if (CanUseJetpack())
    {
        delta = direction * 2;
        playerHasJetpack = false;
        return;
    }
    delta = Vector2i();
}
void Move()
{
    playerPosition += delta;
}

void CheckForPickups()
{
    if (GetMapTile(playerPosition) == TileType::Jetpack)
    {
        playerHasJetpack = true;
        SetMapTile(playerPosition, TileType::Floor);
    }
}

void TryMove()
{
    UpdateMovingDeltas();
    Move();
    CheckForPickups();
}

void PlaceTileInImage(std::string& image, int x, int y)
{
    const int charIndex = (y * (width + 1)) + x;
    image[charIndex] = (char)map[y][x];
}
void PlacePlayerInImage(std::string& image)
{
    const int index = (playerPosition.y * (width + 1)) + playerPosition.x;
    image[index] = playerChar;
}
std::string GetMapImage()
{
    std::string result = std::string((width + 1) * height, '\n');

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
            PlaceTileInImage(result, x, y);
    }

    PlacePlayerInImage(result);

    return result;
}

void ProcessInput(char input)
{
    direction = Vector2i();
    switch (input)
    {
    case 'w':
        direction.y = -1;
        break;
    case 's':
        direction.y = 1;
        break;
    case 'a':
        direction.x = -1;
        break;
    case 'd':
        direction.x = 1;
        break;
    }
}

void Render()
{
    std::system("cls");
    std::string mapImage = GetMapImage();
    std::cout << mapImage;
}

void Input()
{
    char input = _getch();

    ProcessInput(input);
}

void Update()
{
    TryMove();
    timeLeft--;
}

bool HasPlayerWon()
{
    return GetMapTile(playerPosition) == TileType::Finish;
}
bool HasPlayerLost()
{
    bool timeRanOut = timeLeft <= 0;
    bool isPlayerOnSpike = GetMapTile(playerPosition) == TileType::Spike;
    return timeRanOut || isPlayerOnSpike;
}
bool HasGameEnded()
{
    return HasPlayerWon() || HasPlayerLost();
}

void DisplayGameEndMessage()
{
    if (HasPlayerWon())
        std::cout << "(:";
    if (HasPlayerLost())
        std::cout << "):";
}

int main()
{
    GenerateMap();
    RandomizePlayerPosition();

    while (!HasGameEnded())
    {
        Render();
        Input();
        Update();
    }

    DisplayGameEndMessage();
    return 0;
}