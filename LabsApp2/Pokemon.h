#pragma once
#include <SDL_render.h>
#include <string>
#include <vector>

#include "Attack.h"
#include "Enums.h"


struct Pokemon
{
	int id;
	std::string name;

	unsigned int hp;
	unsigned int max_hp;
	unsigned int energy;
	unsigned int max_energy;
	unsigned int weakness;
	unsigned int speed;
	unsigned int attack_count;
	PokemonType type;

	std::vector<Attack> attacks;

	SDL_Texture *texture;

	void destroy();
	void draw(SDL_Renderer*& renderer, int x, int y, int w, int h, bool mirror);
};
