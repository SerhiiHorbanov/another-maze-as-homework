#include <iostream>
#include <vector>
#include <random>

const int width = 10;
const int height = 10;
const int wallFrequencyPercents = 25;

char map[height][width];

char playerChar = '@';
int playerX = 0;
int playerY = 0;
int dx = 0;
int dy = 0;

int finishX = 0;
int finishY = 0;
bool reachedFinish = false;

void GenerateMap()
{
    srand(time(NULL));
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (std::rand() % 100 < wallFrequencyPercents)
                map[y][x] = '#';
            else
                map[y][x] = '.';
        }
    }

    finishX = std::rand() % width;
    finishY = std::rand() % height;

    map[finishY][finishX] = 'F';
}

void RandomizePlayerPosition()
{
    playerX = std::rand() % width;
    playerX = std::rand() % height;
}

bool IsWalkable(char tile)
{
    return tile != '#';
}

bool CanMove()
{
    int toX = playerX + dx;
    int toY = playerY + dy;

    if (toX < 0 || toY < 0)
        return false;
    if (toX >= width || toY >= height)
        return false;

    return IsWalkable(map[toY][toX]);
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

void CheckFinish()
{
    reachedFinish = finishX == playerX && finishY == playerY;
}

bool GameEnded()
{
    return reachedFinish;
}

void Render()
{
    std::system("cls");
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (y == playerY && x == playerX)
            {
                std::cout << playerChar;
                continue;
            }
            std::cout << map[y][x];
        }
        std::cout << '\n';
    }
}

void Input()
{
    std::string input;
    std::cin >> input;

    dy = 0;
    dx = 0;
    switch (input[0])
    {
    case 'w':
    case 'W':
        dy = -1;
        break;
    case 's':
    case 'S':
        dy = 1;
        break;
    case 'a':
    case 'A':
        dx = -1;
        break;
    case 'd':
    case 'D':
        dx = 1;
        break;
    }
}

void Update()
{
    TryMove();
    CheckFinish();
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

    std::cout << "YNNNNNNNNNNN";
}