#include "LoaderTools.h"
#include "Pokemon.h"

#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <SDL_image.h>


std::vector<Pokemon> load_pokemons(const std::string& path, SDL_Renderer*& renderer)
{
	auto pokemons = std::vector<Pokemon>();

	int c = 0;
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		if (is_directory(entry))
		{
			auto pokemon = Pokemon();
			pokemon.name = entry.path().filename().string();
			pokemon.id = c;

			auto texture = IMG_LoadTexture(renderer, entry.path().string().append("/texture.png").data());
			if (!texture)
			{
				std::cout << "IMG_LoadTexture Error: " << SDL_GetError() << '\n';
				continue;
			}
			pokemon.texture = texture;

			std::ifstream file(entry.path().string().append("/stats.txt").data());

			if (!file)
			{
				std::cout << "Error loading stats\n";
				continue;
			}

			file >> pokemon.name;
			file >> pokemon.hp;
			pokemon.max_hp = pokemon.hp;
			file >> pokemon.energy;
			pokemon.max_energy = pokemon.energy;
			file >> pokemon.weakness;
			file >> pokemon.speed;
			int t;
			file >> t;
			pokemon.type = static_cast<PokemonType>(t);
			file >> pokemon.attack_count;

			for (int i = 0; i < pokemon.attack_count; i++)
			{
				auto attack = Attack();
				file.clear();
				file.ignore(9999, '\n');
				std::getline(file, attack.Name, '\n');

				file >> attack.Damage;
				file >> attack.EnergyCost;

				pokemon.attacks.push_back(attack);
			}

			file.close();

			pokemons.push_back(pokemon);
		}
		c++;
	}

	return pokemons;
}
