#pragma once
#include <vector>

#include "Enums.h"
#include "Pokemon.h"

#define PLAYER_COUNT 2

struct GameState
{
	bool IsRunning;
	int Player;
	bool WaitingForInput;
	bool GameOver;

	GameMenu CurrentMenu;
	int MenuItem;
	unsigned int maxMenuItem;

	Pokemon Players[PLAYER_COUNT];

	std::vector<Pokemon>* AllPokemons;
};
