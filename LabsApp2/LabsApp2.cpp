#include <iostream>
#include <SDL.h>
#include <fstream>
#include <SDL_ttf.h>

#include "LoaderTools.h"
#include "GameState.h"
#include "UIUtils.h"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[])
{
	std::cout << "Starting...\n";

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0 ||
		TTF_Init() != 0)
	{
		return 1;
	}

	std::cout << "Initializing display...\n";
	SDL_Window* window = SDL_CreateWindow("SDL2_App!", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	std::cout << "Initialized\n";

	if (window == nullptr)
	{
		return 1;
	}

	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d11");
	auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	const auto pokemons = LoadTextures("data/pokemons/", renderer);

	auto state = GameState();
	state.IsRunning = true;
	state.PlayerOneHP = 100;
	state.PlayerTwoHP = 50;
	long frameCounter = 0;

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
		}

		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 48, 48, 48, 0);
		auto backgroundRect = SDL_Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		SDL_RenderFillRect(renderer, &backgroundRect);

		if (frameCounter % 5 == 0)
		{
			state.PlayerOneHP --;
			state.PlayerTwoHP --;

			if(state.PlayerOneHP <= 0)
				state.PlayerOneHP = 100;

			if(state.PlayerTwoHP <= 0)
				state.PlayerTwoHP = 100;
		}


		DrawUI(renderer, state);

		SDL_RenderPresent(renderer);
	}

	for (auto pok : pokemons)
	{
		pok.Destroy();
	}
	SDL_DestroyWindow(window);

	SDL_Quit();
}
