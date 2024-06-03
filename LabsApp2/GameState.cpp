#include "GameState.h"


Pokemon* GameState::get_current_pokemon()
{
	return &players[player][current_pokemon[player]];
}

std::vector<Pokemon>* GameState::get_player_pokemons()
{
	return &players[player];
}

std::vector<Pokemon>* GameState::get_opponent_pokemons()
{
	return &players[PLAYER_COUNT - player - 1];
}

Pokemon* GameState::get_pokemon(int player, int pokemon)
{
	return &players[player][pokemon];
}

Pokemon* GameState::get_current_player_pokemon(int pokemon)
{
	return &players[player][pokemon];
}

Pokemon* GameState::get_opponent_pokemon(int pokemon)
{
	return &players[PLAYER_COUNT - player - 1][pokemon];
}

Pokemon* GameState::get_opponent_current_pokemon()
{
	return &players[PLAYER_COUNT - player - 1][current_pokemon[PLAYER_COUNT - player - 1]];
}

void GameState::next_player()
{
	player++;
	player %= PLAYER_COUNT;
}

void GameState::menu_up()
{
	menu_item--;
	if (menu_item < 0)
	{
		menu_item = max_menu_item - 1;
	}
}

void GameState::menu_down()
{
	menu_item++;
	menu_item %= max_menu_item;
}

void GameState::regen_mana(int player)
{
	for (int i = 0; i < POKEMON_COUNT; i++)
	{
		for (auto p : players[player])
		{
			if (!p.hp)
				continue;

			p.energy += rand() % 10 + 10;
			if (p.energy > p.max_energy)
				p.energy = p.max_energy;
		}
	}
}
