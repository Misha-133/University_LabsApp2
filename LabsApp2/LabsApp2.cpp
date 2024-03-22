#include <iostream>
#include <SDL.h>
#include <fstream>

#include "LoaderTools.h"

constexpr int SCREEN_WIDTH = 1440;
constexpr int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[])
{
	std::cout << "Starting...\n";

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
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

	auto quit = false;
	while (!quit)
	{
		SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
				case SDL_QUIT: quit = true; break;
			}
		}

		SDL_RenderClear(renderer);

		int posX = 0;
		int posY = 0;
		for (auto& pokemon : *pokemons)
		{
			auto rect = SDL_Rect(posX, posY, 384, 256);
			SDL_RenderCopy(renderer, pokemon.Texture, nullptr, &rect);
			posX += 384;
			if (posX >= SCREEN_WIDTH)
			{
				posX = 0;
				posY += 256;
			}
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);

	SDL_Quit();
}
