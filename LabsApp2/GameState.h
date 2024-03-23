#pragma once
#include "Pokemon.h"

struct GameState
{
	bool IsRunning;
	bool FirstPlayer;
	bool WaitingForInput;

	unsigned int PlayerOneHP;
	unsigned int PlayerTwoHP;

	Pokemon* PlayerOne;
	Pokemon* PlayerTwo;
};
