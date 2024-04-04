#include "LoaderTools.h"
#include "Pokemon.h"

#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <SDL_image.h>


std::vector<Pokemon> LoadPokemons(const std::string& path, SDL_Renderer*& renderer)
{
    auto pokemons = std::vector<Pokemon>();

    int c = 0;
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (is_directory(entry))
        {
            auto pokemon = Pokemon();
            pokemon.Name = entry.path().filename().string();
            pokemon.Id = c;

            auto texture = IMG_LoadTexture(renderer, entry.path().string().append("/texture.png").data());
            if (!texture)
            {
                std::cout << "IMG_LoadTexture Error: " << SDL_GetError() << '\n';
                continue;
            }
            pokemon.Texture = texture;

            std::ifstream file(entry.path().string().append("/stats.txt").data());

            if (!file)
            {
                std::cout << "Error loading stats\n";
                continue;
            }

            file >> pokemon.Name;
            file >> pokemon.HP;
            file >> pokemon.Energy;
            file >> pokemon.Damage;
            file >> pokemon.Weakness;
            file.close();

            pokemons.push_back(pokemon);
        }
        c++;
    }

    return pokemons;
}
