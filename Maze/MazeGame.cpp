#include "MazeGame.h"
#include <random>

void MazeGame::SetRandomSeed()
{
    std::srand(time(NULL));
}

void MazeGame::Run()
{
    SetRandomSeed();

    while (!_map.IsGameEnded())
    {
        Render();
        Input();
        Update();
    }
}

void MazeGame::Render()
{
    std::system("cls");
    _map.Render();
}

void MazeGame::Input()
{
    _input.GetInput();
    _input.ProcessInput();
}

void MazeGame::Update()
{
    _map.Update(_input);
}