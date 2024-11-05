#include <conio.h>
#include "Input.h"

void Input::GetInput()
{
    lastInput = _getch();
}

void Input::ProcessInput()
{
	switch (lastInput)
	{
	case 'w':
		walkDirection = Vector2i(0, -1);
		break;
	case 'a':
		walkDirection = Vector2i(-1, 0);
		break;
	case 's':
		walkDirection = Vector2i(0, 1);
		break;
	case 'd':
		walkDirection = Vector2i(1, 0);
		break;
	}
}

Vector2i Input::GetWalkDirection() const
{
	return walkDirection;
}
