#pragma once
#include <SDL_render.h>
#include <string>

#include "Enums.h"

struct Pokemon
{
	int Id;
	std::string Name;
	int HP;
	int Damage;
	int Weakness;


	SDL_Texture *Texture;

	void Destroy();
};

// display name
// hp
// damage
// weakness