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
	int Weakness;

	std::string AttackOneName;
	unsigned int AttackOneDamage;
	unsigned int AttackOneEnergy;
	int AttackOneType;

	std::string AttackTwoName;
	unsigned int AttackTwoDamage;
	unsigned int AttackTwoEnergy;
	int AttackTwoType;

	SDL_Texture *Texture;

	void Destroy();
	void Draw(SDL_Renderer*& renderer, int x, int y, int w, int h, bool mirror);
};
