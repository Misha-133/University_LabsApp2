#include "Pokemon.h"


void Pokemon::Destroy()
{
	SDL_DestroyTexture(Texture);
}
