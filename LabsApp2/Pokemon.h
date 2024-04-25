#pragma once
#include <SDL_render.h>
#include <string>
#include <vector>

#include "Attack.h"


struct Pokemon
{
	int Id;
	std::string Name;

	unsigned int HP;
	unsigned int Energy;
	unsigned int Weakness;
	unsigned int Speed;
	unsigned int AttackCount;

	std::vector<Attack> Attacks;

	SDL_Texture *Texture;

	void Destroy();
	void Draw(SDL_Renderer*& renderer, int x, int y, int w, int h, bool mirror);
};
