#include <iostream>
#include <SDL.h>
#include <fstream>
#include <SDL_ttf.h>

#include "LoaderTools.h"
#include "GameState.h"
#include "UiElement.h"
#include "UIUtils.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char* argv[])
{
	std::cout << "Starting...\n";

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0 ||
		TTF_Init() != 0)
	{
		return 1;
	}

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
	state.IsRunning = true;
	state.PlayerOneHP = 100;
	state.PlayerTwoHP = 50;
	long frameCounter = 0;

	state.PlayerOne = pokemons.data();
	state.PlayerTwo = &pokemons[1];
	state.PlayerOneHP = state.PlayerOne->HP;
	state.PlayerTwoHP = state.PlayerTwo->HP;

	auto uiElements = LoadUi();

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
			}

			for (auto ui : uiElements)
			{
				ui->HandleEvent(ev);
			}
		}

		SDL_RenderClear(renderer);
		DrawBackground(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

		if (frameCounter % 5 == 0)
		{
			state.PlayerOneHP--;
			state.PlayerTwoHP--;

			if (state.PlayerOneHP <= 0)
				state.PlayerOneHP = state.PlayerOne->HP;

			if (state.PlayerTwoHP <= 0)
				state.PlayerTwoHP = state.PlayerTwo->HP;
		}

		DrawUI(renderer, state, uiElements);

		state.PlayerOne->Draw(renderer, 64, 64, 192, 192, false);
		state.PlayerTwo->Draw(renderer, 384, 64, 192, 192, true);

		SDL_RenderPresent(renderer);
	}

	for (auto pok : pokemons)
	{
		pok.Destroy();
	}
	SDL_DestroyWindow(window);

	SDL_Quit();
}
