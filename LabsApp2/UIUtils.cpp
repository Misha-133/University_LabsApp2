#include "UIUtils.h"
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <vector>

#include "GameState.h"

void draw_ui(SDL_Renderer*& renderer, GameState& state)
{
	if (state.is_running)
	{
		int x = 32;
		int y = 16;
		for (int i = 0; i < PLAYER_COUNT; i++)
		{
			int j = 0;
			for (auto& p : state.players[i])
			{
				draw_health_bar(renderer, x, y, 96, 16, p.hp, p.max_hp);
				draw_energy_bar(renderer, x, y + 20, 96, 16, p.energy, p.max_energy);

				auto r = SDL_Rect(x, y + 40, 96, 96);

				if (state.player == i && state.current_pokemon[i] == j)
				{
					SDL_SetRenderDrawColor(renderer, 128, 128, 96, 0);
					SDL_RenderDrawRect(renderer, &r);
				}

				p.draw(renderer, x, y + 40, 96, 96, i);
				y += 160;
				j++;
			}


			if (state.current_menu == GameMenu_AttackSelection && !state.game_over)
			{
				draw_attack_select(renderer, state, state.get_current_pokemon());
			}
			x += 480;
			y = 16;
		}


		if (state.game_over)
		{
			auto x = 0;
			auto y = 0;
			auto w = 640;
			auto h = 32;
			auto color = SDL_Color(255, 255, 255, 0);
			int hpSum = 0;
			for (auto p : state.players[0])
			{
				hpSum += p.hp;
			}
			std::string str = hpSum == 0 ? "player 2 wins!" : "player 1 wins!";
			draw_text_centered_large(renderer, str, x, y, w, h, color);
		}
	}
	else
	{
		for (int i = 0; i < state.max_menu_item; i++)
		{
			int x = 64;
			int y = 64 + i * 32;
			int w = 256;
			int h = 32;
			auto r = SDL_Rect(x, y, w, h);
			SDL_SetRenderDrawColor(renderer, 32, 32, 32, 0);
			SDL_RenderFillRect(renderer, &r);

			if (state.menu_item == i)
			{
				SDL_SetRenderDrawColor(renderer, 128, 128, 96, 0);
				SDL_RenderFillRect(renderer, &r);

				r = SDL_Rect(x + 2, y + 2, w - 4, h - 4);
				SDL_SetRenderDrawColor(renderer, 32, 32, 32, 0);
				SDL_RenderFillRect(renderer, &r);
			}

			auto color = state.menu_item == i ? SDL_Color(192, 192, 255, 0) : SDL_Color(96, 96, 192, 0);
			draw_text_centered_large(renderer, state.all_pokemons->at(i).name, x, y, w, h, color);


			state.all_pokemons->at(i).draw(renderer, 24, y, 32, 32, false);
		}

		int x = 0;
		int y = 0;
		int w = 640;
		int h = 32;
		auto color = SDL_Color(255, 255, 255, 0);
		if (state.current_menu == GameMenu_PokemonSelection1)
		{
			std::string str = "player 1, choose your Pokemon";
			draw_text_centered_large(renderer, str, x, y, w, h, color);
		}
		else if (state.current_menu == GameMenu_PokemonSelection2)
		{
			std::string str = "player 2, choose your Pokemon";
			draw_text_centered_large(renderer, str, x, y, w, h, color);
		}

	}
}

void draw_attack_select(SDL_Renderer*& renderer, GameState& state, Pokemon* pokemon)
{
	auto attackCount = pokemon->attack_count;

	auto x = 32;
	auto y = POKEMON_COUNT * 128 + 128;
	auto w = 576;
	auto h = 32 * attackCount;
	int h1 = (int)h / attackCount;

	auto border = 2;

	auto rect = SDL_Rect(x, y, w, h);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(renderer, &rect);

	rect = SDL_Rect(x + border, y + border, w - border * 2, h - border * 2);
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 0);
	SDL_RenderFillRect(renderer, &rect);

	SDL_Color color;
	for (int i = 0; i < attackCount; i++)
	{
		int y1 = y + i * 32;
		color = state.menu_item == i ? SDL_Color(32, 32, 255, 0) : SDL_Color(96, 96, 192, 0);
		auto str = pokemon->attacks[i].Name + "     D: " + std::to_string(pokemon->attacks[i].Damage) + "     E: " + std::to_string(pokemon->attacks[i].EnergyCost);
		draw_text_centered_large(renderer, str, x, y1, w, h1, color);
	}
}

void draw_health_bar(SDL_Renderer*& renderer, int x, int y, int w, int h, unsigned int value, unsigned int total)
{
	auto rect = SDL_Rect(x, y, w, h);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(renderer, &rect);

	float percent = (value / (float)total);
	int width = percent * (w - 4);

	rect = SDL_Rect(x + 2, y + 2, width, h - 4);
	SDL_SetRenderDrawColor(renderer, 228 * (1 - percent), 16 + 228 * percent, 32, 0);
	SDL_RenderFillRect(renderer, &rect);

	auto hpColor = SDL_Color(64 + 190 * percent, 192 - 64 * percent, 255 - 192 * percent, 0);

	auto str = std::to_string(value) + "/" + std::to_string(total);

	draw_text_centered_small(renderer, str, x, y, w, h, hpColor);
}

void draw_energy_bar(SDL_Renderer*& renderer, int x, int y, int w, int h, unsigned int value, unsigned int total)
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

	draw_text_centered_small(renderer, str, x, y, w, h, hpColor);
}

void draw_text_centered_small(SDL_Renderer*& renderer, std::string& text, int& x, int& y, int& w, int& h, SDL_Color& color)
{
	static auto sans = TTF_OpenFont("data/fonts/main_font.ttf", 12);

	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(sans, text.data(), color);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect rect = { x + (w / 2) - surfaceMessage->w / 2, y + (h / 2) - surfaceMessage->h / 2, surfaceMessage->w, surfaceMessage->h };

	SDL_RenderCopy(renderer, message, nullptr, &rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

void draw_text_centered_large(SDL_Renderer*& renderer, std::string& text, int& x, int& y, int& w, int& h, SDL_Color& color)
{
	static auto sans = TTF_OpenFont("data/fonts/main_font.ttf", 24);

	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(sans, text.data(), color);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect rect = { x + (w / 2) - surfaceMessage->w / 2, y + (h / 2) - surfaceMessage->h / 2, surfaceMessage->w, surfaceMessage->h };

	SDL_RenderCopy(renderer, message, nullptr, &rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

void draw_background(SDL_Renderer*& renderer, int w, int h, SDL_Texture* background_image)
{
	auto backgroundRect = SDL_Rect(0, 0, w, h);
	SDL_RenderCopyEx(renderer, background_image, nullptr, &backgroundRect, 0, 0, SDL_FLIP_NONE);
}