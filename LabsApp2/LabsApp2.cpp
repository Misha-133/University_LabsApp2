#include <iostream>
#include <SDL.h>


constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[])
{
    std::cout << "Starting...\n";
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 App!", SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (window == nullptr)
    {
        return 1;
    }

    SDL_Surface* screen_surface = SDL_GetWindowSurface(window);

    SDL_FillRect(screen_surface, nullptr, SDL_MapRGB(screen_surface->format, 0, 255, 64));

    SDL_UpdateWindowSurface(window);

    SDL_Delay(15000);

    SDL_DestroyWindow(window);

    SDL_Quit();
}
