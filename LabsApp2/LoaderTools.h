#pragma once
#include <string>
#include <vector>

#include "Pokemon.h"

std::vector<Pokemon> LoadPokemons(const std::string&, SDL_Renderer*&);
