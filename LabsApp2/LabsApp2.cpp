#include <algorithm>
#include <iostream>
#include <SDL.h>
#include <fstream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Enums.h"
#include "GameLogic.h"
#include "LoaderTools.h"
#include "GameState.h"
#include "UIUtils.h"


int main(int argc, char* argv[])
{
	std::cout << "Starting...\n";

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0 || TTF_Init() != 0)
		return 1;

	if (SDL_Init(SDL_INIT_AUDIO) != 0)
		return 1;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music* bgm = Mix_LoadMUS("data/music/music1.mp3");
	Mix_PlayMusic(bgm, 999);

	std::cout << "Initializing display...\n";
	SDL_Window* window = SDL_CreateWindow("Pokokek", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	std::cout << "Initialized\n";

	if (window == nullptr)
	{
		return 1;
	}

	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d11");
	auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	auto background = IMG_LoadTexture(renderer, "data/images/background.png");
	if (!background)
	{
		std::cout << "Failed loading background image" << SDL_GetError() << '\n';
	}	

	auto pokemons = load_pokemons("data/pokemons/", renderer);

	auto state = GameState();

	long frameCounter = 0;

	state.all_pokemons = &pokemons;

	state.current_menu = GameMenu_PokemonSelection1;
	state.menu_item = 0;
	state.max_menu_item = pokemons.size();

	try {
		auto quit = false;
		while (!quit)
		{
			frameCounter++;
			SDL_Event ev;
			while (SDL_PollEvent(&ev))
			{
				switch (ev.type)
				{
				case SDL_QUIT: quit = true; break;
				case SDL_KEYDOWN:
				{
					switch (ev.key.keysym.sym)
					{
					case SDLK_UP:
						state.menu_up();
						break;

					case SDLK_DOWN:
						state.menu_down();
						break;
					case SDLK_KP_ENTER:
					case SDLK_RETURN:
						if (state.current_menu == GameMenu_AttackSelection && !state.game_over)
						{
							damage_player(*state.get_current_pokemon(), *state.get_opponent_current_pokemon(), state.menu_item);

							state.regen_mana(PLAYER_COUNT - state.player - 1);

							state.next_player();

							for (int i = 0; i < state.players[state.player].size(); i++)
							{
								state.current_pokemon[state.player]++;
								state.current_pokemon[state.player] %= state.players[state.player].size();

								if (state.players[state.player].at(state.current_pokemon[state.player]).hp != 0)
									break;
							}

							state.max_menu_item = state.get_current_pokemon()->attack_count;
							state.menu_item = 0;
						}
						else if (state.current_menu == GameMenu_PokemonSelection1)
						{
							state.players[0].push_back(pokemons[state.menu_item]);
							state.menu_item = 0;

							if (state.players[0].size() >= POKEMON_COUNT)
								state.current_menu = GameMenu_PokemonSelection2;
						}
						else if (state.current_menu == GameMenu_PokemonSelection2)
						{
							state.players[1].push_back(pokemons[state.menu_item]);

							state.menu_item = 0;
							if (state.players[1].size() >= POKEMON_COUNT)
								state.current_menu = GameMenu_Starting;
						}
						break;
					}
				}
				break;
				}
			}
			if (state.current_menu == GameMenu_Starting)
			{
				unsigned int maxSpeed = state.get_pokemon(0, 0)->speed;
				int maxSpeedPlayer = 0;
				int maxSpeedIndex = 0;
				for (int i = 0; i < PLAYER_COUNT; i++)
				{
					int j = 0;
					for (auto& p : state.players[i])
					{
						if (p.speed > maxSpeed)
						{
							maxSpeed = p.speed;
							maxSpeedIndex = j;
							maxSpeedPlayer = i;
						}
						j++;
					}
				}
				state.player = maxSpeedPlayer;
				state.max_menu_item = state.get_current_player_pokemon(maxSpeedIndex)->attack_count;
				state.current_pokemon[state.player] = maxSpeedIndex;
				state.menu_item = 0;

				state.is_running = true;
				state.current_menu = GameMenu_AttackSelection;
			}

			if (state.is_running)
			{
				for (int i = 0; i < PLAYER_COUNT; i++)
				{
					int hpSum = 0;
					for (auto& p : state.players[i])
					{
						hpSum += p.hp;
					}
					if (!hpSum)
						state.game_over = true;
				}
			}

			SDL_RenderClear(renderer);
			draw_background(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, background);

			draw_ui(renderer, state);

			SDL_RenderPresent(renderer);
		}

		SDL_DestroyTexture(background);
		for (auto pok : pokemons)
		{
			pok.destroy();
		}
		SDL_DestroyWindow(window);
		Mix_FreeMusic(bgm);
		Mix_CloseAudio();

		SDL_Quit();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
