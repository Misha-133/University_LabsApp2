#include "Pokemon.h"


void Pokemon::Destroy()
{
	SDL_DestroyTexture(Texture);
}

void Pokemon::Draw(SDL_Renderer*& renderer, int x, int y, int w, int h, bool mirror)
{
	SDL_Rect rect = { x, y, w, h };
	if (!mirror)
		SDL_RenderCopyEx(renderer, Texture, nullptr, &rect, 0, 0, SDL_FLIP_NONE);
	else
		SDL_RenderCopyEx(renderer, Texture, nullptr, &rect, 0, 0, SDL_FLIP_HORIZONTAL);
}
