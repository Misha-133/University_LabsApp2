#pragma once
#include <string>
#include <vector>

#include "Pokemon.h"

std::vector<Pokemon> load_pokemons(const std::string&, SDL_Renderer*&);
