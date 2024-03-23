#include "UIUtils.h"
#include <SDL_render.h>
#include "GameState.h"

void DrawUI(SDL_Renderer*& renderer, GameState& state)
{
	if (state.IsRunning)
	{
		DrawHealthBar(renderer, 0, 0, 128, 16, state.PlayerOneHP, 100);
	}
}

void DrawHealthBar(SDL_Renderer*& renderer, int x, int y, int w, int h, int value, int total)
{
	auto rect = SDL_Rect(x, y, w, h);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(renderer, &rect);

	int width = (value / (float)total) * (w - 4);

	rect = SDL_Rect(x + 2, y + 2, width, h - 4);
	SDL_SetRenderDrawColor(renderer, 255, 16, 32, 0);
	SDL_RenderFillRect(renderer, &rect);
}