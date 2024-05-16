#include <algorithm>
#include <iostream>
#include <SDL.h>
#include <fstream>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Enums.h"
#include "GameLogic.h"
#include "LoaderTools.h"
#include "GameState.h"
#include "UIUtils.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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

	auto pokemons = LoadPokemons("data/pokemons/", renderer);

	auto state = GameState();

	long frameCounter = 0;

	state.AllPokemons = &pokemons;

	state.CurrentMenu = GameMenu_PokemonSelection1;
	state.MenuItem = 0;
	state.maxMenuItem = pokemons.size();

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
					if (state.MenuItem > 0)
						state.MenuItem--;
					else
						state.MenuItem = state.maxMenuItem - 1;
					break;

				case SDLK_DOWN:
					if (state.MenuItem < state.maxMenuItem - 1)
						state.MenuItem++;
					else
						state.MenuItem = 0;
					break;
				case SDLK_KP_ENTER:
				case SDLK_RETURN:
					if (state.CurrentMenu == GameMenu_AttackSelection && !state.GameOver)
					{
						DamagePokemon(state.Players[state.Player], state.Players[PLAYER_COUNT - state.Player - 1], state.MenuItem);

						state.Players[PLAYER_COUNT - state.Player - 1].Energy += rand() % 20;
						if (state.Players[PLAYER_COUNT - state.Player - 1].Energy > state.Players[PLAYER_COUNT - state.Player - 1].MaxEnergy)
							state.Players[PLAYER_COUNT - state.Player - 1].Energy = state.Players[PLAYER_COUNT - state.Player - 1].MaxEnergy;

						state.Player++;
						state.Player %= 2;
						state.MenuItem = 0;
						state.maxMenuItem = state.Players[state.Player].AttackCount;
					}
					else if (state.CurrentMenu == GameMenu_PokemonSelection1)
					{
						state.Players[0] = pokemons[state.MenuItem];
						state.CurrentMenu = GameMenu_PokemonSelection2;
					}
					else if (state.CurrentMenu == GameMenu_PokemonSelection2)
					{
						state.Players[1] = pokemons[state.MenuItem];
						state.CurrentMenu = GameMenu_AttackSelection;

						unsigned int maxSpeed = state.Players[0].Speed;
						int maxSpeedIndex = 0;
						for (int i = 1; i < PLAYER_COUNT; i++)
							if (state.Players[i].Speed > maxSpeed)
								{
								maxSpeed = state.Players[i].Speed;
								maxSpeedIndex = i;
							}

						state.Player = maxSpeedIndex;
						state.maxMenuItem = state.Players[state.Player].AttackCount;

						state.IsRunning = true;
					}
					break;
				}
			}
			break;
			}
		}

		if (state.IsRunning)
		{
			for (int i = 0; i < PLAYER_COUNT; i++)
			{
				if (!state.Players[i].HP)
					state.GameOver = true;
			}
		}

		SDL_RenderClear(renderer);
		DrawBackground(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

		DrawUI(renderer, state);

		SDL_RenderPresent(renderer);
	}

	for (auto pok : pokemons)
	{
		pok.Destroy();
	}
	SDL_DestroyWindow(window);
	Mix_FreeMusic(bgm);
	Mix_CloseAudio();

	SDL_Quit();
}