#include "UIUtils.h"
#include <SDL_render.h>
#include <SDL_ttf.h>
#include "GameState.h"

void DrawUI(SDL_Renderer*& renderer, const GameState& state)
{
	if (state.IsRunning)
	{
		DrawHealthBar(renderer, 0, 0, 192, 32, state.PlayerOneHP, 100);
		DrawHealthBar(renderer, 448, 0, 192, 32, state.PlayerTwoHP, 100);
	}
}

void DrawHealthBar(SDL_Renderer*& renderer, const int x, const int y, const int w, const int h, const unsigned int value, const unsigned int total)
{
	auto rect = SDL_Rect(x, y, w, h);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(renderer, &rect);

	const float percent = (value / (float)total);
	const int width = percent * (w - 4);

	rect = SDL_Rect(x + 2, y + 2, width, h - 4);
	SDL_SetRenderDrawColor(renderer, 228 * (1 - percent), 16 + 228 * percent, 32, 0);
	SDL_RenderFillRect(renderer, &rect);

	static auto sans = TTF_OpenFont("data/fonts/ms_comic_sans.ttf", 18);
	const auto hpColor = SDL_Color(64 + 190 * percent, 192 - 64 * percent, 255 - 192 * percent, 0);

	auto str = std::to_string(value) + "/" + std::to_string(total);

	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(sans, str.data(), hpColor);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	rect = { x + (w / 2) - surfaceMessage->w / 2, y + 4, surfaceMessage->w, surfaceMessage->h };

	SDL_RenderCopy(renderer, message, nullptr, &rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}