#pragma once
#include <vector>

#include "Enums.h"
#include "Pokemon.h"

#define PLAYER_COUNT 2
#define POKEMON_COUNT 3


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640

struct GameState
{
	bool is_running;
	int player;
	bool waiting_for_input;
	bool game_over;

	GameMenu current_menu;
	int menu_item;
	unsigned int max_menu_item;

	std::vector<Pokemon> players[PLAYER_COUNT];
	int current_pokemon[PLAYER_COUNT];

	std::vector<Pokemon>* all_pokemons;

	Pokemon* get_current_pokemon();
	Pokemon* get_opponent_current_pokemon();

	std::vector<Pokemon>* get_player_pokemons();
	std::vector<Pokemon>* get_opponent_pokemons();

	Pokemon* get_pokemon(int player, int pokemon);

	Pokemon* get_current_player_pokemon(int pokemon);
	Pokemon* get_opponent_pokemon(int pokemon);

	void next_player();

	void menu_up();
	void menu_down();

	void regen_mana(int player);
};
