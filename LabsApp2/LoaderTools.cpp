﻿#include "LoaderTools.h"
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
			pokemon.MaxHP = pokemon.HP;
			file >> pokemon.Energy;
			pokemon.MaxEnergy = pokemon.Energy;
			file >> pokemon.Weakness;
			file >> pokemon.Speed;
			int t;
			file >> t;
			pokemon.Type = static_cast<PokemonType>(t);
			file >> pokemon.AttackCount;

			for (int i = 0; i < pokemon.AttackCount; i++)
			{
				auto attack = Attack();
				file.clear();
				file.ignore(9999, '\n');
				std::getline(file, attack.Name, '\n');

				file >> attack.Damage;
				file >> attack.EnergyCost;

				pokemon.Attacks.push_back(attack);
			}

			file.close();

			pokemons.push_back(pokemon);
		}
		c++;
	}

	return pokemons;
}
