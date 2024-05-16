#pragma once
#include <SDL_render.h>
#include <string>
#include <vector>

#include "Attack.h"
#include "Enums.h"


struct Pokemon
{
	int Id;
	std::string Name;

	unsigned int HP;
	unsigned int MaxHP;
	unsigned int Energy;
	unsigned int MaxEnergy;
	unsigned int Weakness;
	unsigned int Speed;
	unsigned int AttackCount;
	PokemonType Type;

	std::vector<Attack> Attacks;

	SDL_Texture *Texture;

	void Destroy();
	void Draw(SDL_Renderer*& renderer, int x, int y, int w, int h, bool mirror);
};
