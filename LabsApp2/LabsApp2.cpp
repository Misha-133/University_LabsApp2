#include <iostream>
#include <SDL.h>
#include <fstream>
#include <SDL_image.h>

constexpr int SCREEN_WIDTH = 640;
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

    auto render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_RenderPresent(render);


    auto bit = IMG_Load("data/pokemons/den/texture.png");
	if (!bit)
    {
        std::cout << "IMG_Load Error: " << IMG_GetError() << std::endl;
        return 1;
    }

    auto texture = SDL_CreateTextureFromSurface(render, bit);
    if (!texture)
    {
        std::cout << "CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(bit);
        return 1;
    }
    SDL_FreeSurface(bit);


    SDL_RenderCopy(render, texture, nullptr, nullptr);
    SDL_RenderPresent(render);


    SDL_Delay(85000);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    SDL_Quit();
}
