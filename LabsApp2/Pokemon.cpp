#include "Pokemon.h"


void Pokemon::destroy()
{
	SDL_DestroyTexture(texture);
}

void Pokemon::draw(SDL_Renderer*& renderer, int x, int y, int w, int h, bool mirror)
{
	SDL_Rect rect = { x, y, w, h };
	if (!mirror)
		SDL_RenderCopyEx(renderer, texture, nullptr, &rect, 0, 0, SDL_FLIP_NONE);
	else
		SDL_RenderCopyEx(renderer, texture, nullptr, &rect, 0, 0, SDL_FLIP_HORIZONTAL);
}
