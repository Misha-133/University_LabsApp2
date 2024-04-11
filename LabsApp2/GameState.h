#pragma once
#include "Pokemon.h"

struct GameState
{
	bool IsRunning;
	bool FirstPlayer;
	bool WaitingForInput;

	GameMenu CurrentMenu;
	int MenuItem;

	unsigned int PlayerOneHP;
	unsigned int PlayerTwoHP;

	unsigned int PlayerOneEnergy;
	unsigned int PlayerTwoEnergy;

	Pokemon* PlayerOne;
	Pokemon* PlayerTwo;
};
