#pragma once
#include <vector>

#include "Pokemon.h"

struct GameState
{
	bool IsRunning;
	bool FirstPlayer;
	bool WaitingForInput;

	GameMenu CurrentMenu;
	int MenuItem;
	int maxMenuItem;

	unsigned int PlayerOneHP;
	unsigned int PlayerTwoHP;

	unsigned int PlayerOneEnergy;
	unsigned int PlayerTwoEnergy;

	Pokemon* PlayerOne;
	Pokemon* PlayerTwo;

	std::vector<Pokemon>* AllPokemons;
};
