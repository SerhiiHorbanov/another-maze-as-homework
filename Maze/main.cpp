#include <conio.h>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>

const int width = 10;
const int height = 10;
const int wallsFrequencyPercents = 25;


enum class TileType : char
{
    Wall = '#',
    Floor = '.',
    Finish = 'F',
    Jetpack = 'J'
};
const char playerChar = '@';

TileType map[height][width];
int timeLeft = 20;

int playerX = 0;
int playerY = 0;

bool playerHasJetpack = false;

int directionX = 0;
int directionY = 0;

int dx = 0;
int dy = 0;

std::pair<int, int> GetRandomMapPosition()
{
    int x = std::rand() % width;
    int y = std::rand() % height;

    return { x, y };
}

TileType GenerateTile()
{
    if (std::rand() % 100 < wallsFrequencyPercents)
        return TileType::Wall;
    return TileType::Floor;
}
void ReplaceRandomTileOfTypeWith(TileType newTile, TileType replaced)
{
    std::vector<TileType&> possibleReplcedTilesPositions = std::vector<TileType&>();
    possibleReplcedTilesPositions.reserve(width * height);

    
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (map[y][x] == replaced)
                possibleReplcedTilesPositions.push_back(map[y][x]);
        }
    }

    const int possibleReplcedTilesPositionsAmount = possibleReplcedTilesPositions.size();
    if (possibleReplcedTilesPositionsAmount == 0)
        return;

    const int randomIndex = std::rand() % possibleReplcedTilesPositionsAmount;
    possibleReplcedTilesPositions[randomIndex] = newTile;
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
    std::pair<int, int> newPosition = GetRandomMapPosition();
    playerX = newPosition.first;
    playerY = newPosition.second;
}

bool IsWalkable(TileType tile)
{
    return tile != TileType::Wall && !(playerHasJetpack && tile == TileType::Jetpack);
}
bool isInMapBounds(int x, int y)
{
    bool NotTooLow = x >= 0 && y >= 0;
    return x < width && y < height;
}
bool CanMoveTo(int tileX, int tileY)
{
    if (isInMapBounds(tileX, tileY))
        return IsWalkable(map[tileY][tileX]);
    return false;
}

bool CanWalk()
{
    int toX = playerX + directionX;
    int toY = playerY + directionY;
    return CanMoveTo(toX, toY);
}
bool CanUseJetpack()
{
    if (!playerHasJetpack)
        return false;

    int toX = playerX + (directionX * 2);
    int toY = playerY + (directionY * 2);
    return CanMoveTo(toX, toY);
}

void UpdateMovingDeltas()
{
    if (CanWalk())
    {
        dx = directionX;
        dy = directionY;
        return;
    }
    if (CanUseJetpack())
    {
        dx = directionX * 2;
        dy = directionY * 2;
        playerHasJetpack = false;
        return;
    }
    dx = 0;
    dy = 0;
}
void Move()
{
    playerX += dx;
    playerY += dy;
}

void CheckForPickups()
{
    if (map[playerY][playerX] == TileType::Jetpack)
    {
        playerHasJetpack = true;
        map[playerY][playerX] = TileType::Floor;
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
    const int index = playerY * (width + 1) + playerX;
    image[index] = playerChar;
}
std::string GetImage()
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
    directionY = 0;
    directionX = 0;
    switch (input)
    {
    case 'w':
        directionY = -1;
        break;
    case 's':
        directionY = 1;
        break;
    case 'a':
        directionX = -1;
        break;
    case 'd':
        directionX = 1;
        break;
    }
}

void Render()
{
    std::system("cls");
    std::string image = GetImage();
    std::cout << image;
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
    return map[playerY][playerX] == TileType::Finish;
}
bool HasPlayerLost()
{
    return timeLeft <= 0;
}
bool HasGameEnded()
{
    return HasPlayerWon() || HasPlayerLost();
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

    return 0;
}