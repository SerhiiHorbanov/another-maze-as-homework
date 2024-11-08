#include <conio.h>
#include <iostream>
#include <random>
#include <tuple>

const int width = 10;
const int height = 10;
const int wallsFrequencyPercents = 25;

char map[height][width];

const char playerChar = '@';
const char wallChar = '#';
const char floorChar = '.';
const char finishChar = 'F';

int playerX = 0;
int playerY = 0;

int dx = 0;
int dy = 0;

char GenerateTile()
{
    if (std::rand() % 100 < wallsFrequencyPercents)
        return wallChar;
    return floorChar;
}

std::pair<int, int> GetRandomMapPosition()
{
    int x = std::rand() % width;
    int y = std::rand() % height;

    return { x, y };
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

    std::pair<int, int> finishPosition = GetRandomMapPosition();
    map[finishPosition.first][finishPosition.second] = finishChar;
}

void RandomizePlayerPosition()
{
    std::pair<int, int> newPosition = GetRandomMapPosition();
    playerX = newPosition.first;
    playerY = newPosition.second;
}

bool IsWalkable(char tile)
{
    return tile != wallChar;
}

bool isInMapBounds(int x, int y)
{
    bool NotTooLow = x >= 0 && y >= 0;
    return x < width && y < height;
}

bool CanMove()
{
    int toX = playerX + dx;
    int toY = playerY + dy;

    if (isInMapBounds(toX, toY))
        return IsWalkable(map[toY][toX]);
    return false;
}

void Move()
{
    playerX += dx;
    playerY += dy;
}

void TryMove()
{
    if (CanMove())
        Move();
}

bool GameEnded()
{
    return map[playerY][playerX] == finishChar;
}

void PlacePlayerInImage(std::string& image)
{
    const int index = playerY * (width + 1) + playerX;
    image[index] = playerChar;
}

void PlaceTileInImage(std::string& image, int x, int y)
{
    const int charIndex = (y * (width + 1)) + x;
    image[charIndex] = map[y][x];
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

void Render()
{
    std::system("cls");
    std::string image = GetImage();
    std::cout << image;
}

void ProcessInput(char input)
{
    dy = 0;
    dx = 0;
    switch (input)
    {
    case 'w':
        dy = -1;
        break;
    case 's':
        dy = 1;
        break;
    case 'a':
        dx = -1;
        break;
    case 'd':
        dx = 1;
        break;
    }
}

void Input()
{
    char input = _getch();

    ProcessInput(input);
}

void Update()
{
    TryMove();
}

int main()
{
    GenerateMap();
    RandomizePlayerPosition();

    while (!GameEnded())
    {
        Render();
        Input();
        Update();
    }

    return 0;
}