#include "UIUtils.h"
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <vector>

#include "GameState.h"

void DrawUI(SDL_Renderer*& renderer, GameState& state)
{
	if (state.IsRunning)
	{
		DrawHealthBar(renderer, 0, 0, 192, 32, state.Players[0].HP, state.Players[0].MaxHP);
		DrawHealthBar(renderer, 448, 0, 192, 32, state.Players[1].HP, state.Players[1].HP);

		DrawEnergyBar(renderer, 0, 40, 192, 32, state.Players[0].Energy, state.Players[0].MaxEnergy);
		DrawEnergyBar(renderer, 448, 40, 192, 32, state.Players[1].Energy, state.Players[1].MaxEnergy);

		if (state.CurrentMenu == GameMenu_AttackSelection && !state.GameOver)
		{
			DrawAttackSelect(renderer, state, &state.Players[state.Player]);
		}

		state.Players[0].Draw(renderer, 64, 96, 192, 192, false);
		state.Players[1].Draw(renderer, 384, 96, 192, 192, true);

		if (state.GameOver)
		{
			auto x = 0;
			auto y = 0;
			auto w = 640;
			auto h = 32;
			auto color = SDL_Color(255, 255, 255, 0);
			std::string str = state.Players[0].HP == 0 ? "Player 2 wins!" : "Player 1 wins!";
			DrawTextCentered(renderer, str, x, y, w, h, color);
		}
	}
	else
	{
		for (int i = 0; i < state.maxMenuItem; i++)
		{
			int x = 64;
			int y = 64 + i * 32;
			int w = 256;
			int h = 32;
			auto color = state.MenuItem == i ? SDL_Color(32, 32, 255, 0) : SDL_Color(96, 96, 192, 0);
			DrawTextCentered(renderer, state.AllPokemons->at(i).Name, x, y, w, h, color);
			if (state.MenuItem == i)
			{
				auto r = SDL_Rect(x, y, w, h);
				SDL_SetRenderDrawColor(renderer, 64, 64, 96, 0);
				SDL_RenderDrawRect(renderer, &r);
			}

			state.AllPokemons->at(i).Draw(renderer, 24, y, 32, 32, false);
		}

		int x = 0;
		int y = 0;
		int w = 640;
		int h = 32;
		auto color = SDL_Color(255, 255, 255, 0);
		if (state.CurrentMenu == GameMenu_PokemonSelection1)
		{
			std::string str = "Player 1, choose your Pokemon";
			DrawTextCentered(renderer, str, x, y, w, h, color);
		}
		else if (state.CurrentMenu == GameMenu_PokemonSelection2)
		{
			std::string str = "Player 2, choose your Pokemon";
			DrawTextCentered(renderer, str, x, y, w, h, color);
		}
		
	}
}

void DrawAttackSelect(SDL_Renderer*& renderer, GameState& state, Pokemon* pokemon)
{
	auto attackCount = state.Players[state.Player].AttackCount;

	auto x = 32;
	auto y = 384;
	auto w = 576;
	auto h = 32 * attackCount;
	int h1 = (int)h / attackCount;

	auto border = 2;

	auto rect = SDL_Rect(x, y, w, h);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(renderer, &rect);

	rect = SDL_Rect(x + border, y + border, w - border * 2, h - border * 2);
	SDL_SetRenderDrawColor(renderer, 128, 128,128, 0);
	SDL_RenderFillRect(renderer, &rect);

	SDL_Color color;
	for (int i = 0; i < attackCount; i++) 
	{
		int y1 = y + i * 32;
		color = state.MenuItem == i ? SDL_Color(32, 32, 255, 0) : SDL_Color(96, 96, 192, 0);
		auto str = pokemon->Attacks[i].Name + "     D: " + std::to_string(pokemon->Attacks[i].Damage) + "     E: " + std::to_string(pokemon->Attacks[i].EnergyCost);
		DrawTextCentered(renderer, str, x, y1, w, h1, color);
	}
}

void DrawHealthBar(SDL_Renderer*& renderer, int x, int y, int w, int h, unsigned int value, unsigned int total)
{
	auto rect = SDL_Rect(x, y, w, h);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(renderer, &rect);

	const float percent = (value / (float)total);
	const int width = percent * (w - 4);

	rect = SDL_Rect(x + 2, y + 2, width, h - 4);
	SDL_SetRenderDrawColor(renderer, 228 * (1 - percent), 16 + 228 * percent, 32, 0);
	SDL_RenderFillRect(renderer, &rect);

	auto hpColor = SDL_Color(64 + 190 * percent, 192 - 64 * percent, 255 - 192 * percent, 0);

	auto str = std::to_string(value) + "/" + std::to_string(total);

	DrawTextCentered(renderer, str, x, y, w, h, hpColor);
}

void DrawEnergyBar(SDL_Renderer*& renderer, int x, int y, int w, int h, unsigned int value, unsigned int total)
{
	auto rect = SDL_Rect(x, y, w, h);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(renderer, &rect);

	const float percent = (value / (float)total);
	const int width = percent * (w - 4);

	rect = SDL_Rect(x + 2, y + 2, width, h - 4);
	SDL_SetRenderDrawColor(renderer, 32, 228 * (1 - percent), 16 + 228 * percent, 0);
	SDL_RenderFillRect(renderer, &rect);

	auto hpColor = SDL_Color(255 - 192 * percent, 192 - 64 * percent, 64 + 190 * percent, 0);

	auto str = std::to_string(value) + "/" + std::to_string(total);

	DrawTextCentered(renderer, str, x, y, w, h, hpColor);
}


void DrawText(SDL_Renderer*& renderer, std::string& text, int& x, int& y, SDL_Color& color)
{
	static auto sans = TTF_OpenFont("data/fonts/main_font.ttf", 18);

	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(sans, text.data(), color);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect rect = { x, y, surfaceMessage->w, surfaceMessage->h };

	SDL_RenderCopy(renderer, message, nullptr, &rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

void DrawTextCentered(SDL_Renderer*& renderer, std::string& text, int& x, int& y, int& w, int& h, SDL_Color& color)
{
	static auto sans = TTF_OpenFont("data/fonts/main_font.ttf", 18);

	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(sans, text.data(), color);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect rect = { x + (w / 2) - surfaceMessage->w / 2, y + (h / 2) - surfaceMessage->h / 2, surfaceMessage->w, surfaceMessage->h};

	SDL_RenderCopy(renderer, message, nullptr, &rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

void DrawBackground(SDL_Renderer*& renderer, int w, int h)
{
	SDL_SetRenderDrawColor(renderer, 48, 48, 48, 0);
	auto backgroundRect = SDL_Rect(0, 0, w, h);
	SDL_RenderFillRect(renderer, &backgroundRect);
}