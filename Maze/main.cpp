#include <conio.h>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>

std::pair<int, int> operator+(const std::pair<int, int> left, const std::pair<int, int>right)
{
    return std::pair<int, int>(left.first + right.first, left.second + right.second);
}
std::pair<int, int> operator*(const std::pair<int, int> left, const int right)
{
    return std::pair<int, int>(left.first * right, left.second * right);
}
void operator+=(std::pair<int, int>& left, const std::pair<int, int> right)
{
    left = left + right;
}

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

std::pair<int, int> playerPosition;

bool playerHasJetpack = false;

std::pair<int, int> direction;
std::pair<int, int> delta;

TileType GetMapTile(std::pair<int, int> position)
{
    return map[position.second][position.first];
}
TileType GetMapTile(int x, int y)
{
    return map[y][x];
}
void SetMapTile(std::pair<int, int> position, TileType tile)
{
    map[position.second][position.first] = tile;
}
std::pair<int, int> GetRandomMapPosition()
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
    std::vector<TileType*> replcableTiles = std::vector<TileType*>();
    replcableTiles.reserve(width * height);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (map[y][x] == replaced)
                replcableTiles.push_back(&map[y][x]);
        }
    }

    const int replacableTilesAmount = replcableTiles.size();
    if (replacableTilesAmount == 0)
        return;

    const int randomIndex = std::rand() % replacableTilesAmount;
    *replcableTiles[randomIndex] = newTile;
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
    std::pair<int, int> newPosition;
    do
        newPosition = GetRandomMapPosition();
    while (GetMapTile(newPosition) == TileType::Finish);
    SetMapTile(newPosition, TileType::Floor);
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
bool isInMapBounds(std::pair<int, int> position)
{
    return isInMapBounds(position.first, position.second);
}
bool CanWalk()
{
    std::pair<int, int> toPosition = playerPosition + direction;
    if (!isInMapBounds(toPosition))
        return false;
    return IsWalkable(GetMapTile(toPosition));
}
bool CanUseJetpack()
{
    if (!playerHasJetpack)
        return false;

    std::pair<int, int> flyingOverPosition = playerPosition + direction;
    std::pair<int, int> toPosition = playerPosition + (direction * 2);

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
    delta = std::pair<int, int>();
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
    const int index = (playerPosition.second * (width + 1)) + playerPosition.first;
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
    direction = std::pair<int, int>();
    switch (input)
    {
    case 'w':
        direction.second = -1;
        break;
    case 's':
        direction.second = 1;
        break;
    case 'a':
        direction.first = -1;
        break;
    case 'd':
        direction.first = 1;
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