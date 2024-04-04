#pragma once
#include <SDL_render.h>
#include <string>

#include "Enums.h"

struct Pokemon
{
	int Id;
	std::string Name;

	int HP;
	int Energy;
	int Damage;
	int Weakness;


	SDL_Texture *Texture;

	void Destroy();
	void Draw(SDL_Renderer*& renderer, int x, int y, int w, int h, bool mirror);
};

// display name
// hp
// energy
// damage
// weakness