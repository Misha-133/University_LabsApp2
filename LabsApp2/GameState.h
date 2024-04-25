#pragma once
#include <vector>

#include "Enums.h"
#include "Pokemon.h"

struct GameState
{
	bool IsRunning;
	bool FirstPlayer;
	bool WaitingForInput;
	bool GameOver;

	GameMenu CurrentMenu;
	int MenuItem;
	unsigned int maxMenuItem;

	unsigned int PlayerOneHP;
	unsigned int PlayerTwoHP;

	unsigned int PlayerOneEnergy;
	unsigned int PlayerTwoEnergy;

	Pokemon* PlayerOne;
	Pokemon* PlayerTwo;

	std::vector<Pokemon>* AllPokemons;
};
