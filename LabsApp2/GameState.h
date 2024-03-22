#pragma once

struct GameState
{
	bool IsRunning;
	bool FirstPlayer;
	bool WaitingForInput;

	unsigned int PlayerOneHP;
	unsigned int PlayerTwoHP;
};
