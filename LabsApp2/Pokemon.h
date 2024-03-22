#pragma once
#include <SDL_render.h>
#include <string>

struct Pokemon
{
	int Id;
	std::string Name;

	SDL_Texture *Texture;

	void Destroy();
};
