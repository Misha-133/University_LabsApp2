#include "LoaderTools.h"
#include "Pokemon.h"

#include <iostream>
#include <vector>
#include <filesystem>
#include <SDL_image.h>


std::vector<Pokemon>* LoadTextures(const std::string& path, SDL_Renderer*& renderer)
{
    auto pokemons = new std::vector<Pokemon>();

    int c = 0;
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (is_directory(entry))
        {
            auto pokemon = Pokemon();
            pokemon.Name = entry.path().filename().string();
            pokemon.Id = c;

            std::cout << entry.path().string();

            auto texture = IMG_LoadTexture(renderer, entry.path().string().append("/texture.png").data());
            if (!texture)
            {
                std::cout << "IMG_LoadTexture Error: " << SDL_GetError() << '\n';
                continue;
            }
            pokemon.Texture = texture;

            pokemons->push_back(pokemon);
        }
        c++;
    }

    return pokemons;
}
