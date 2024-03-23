#pragma once
#include <SDL_render.h>
#include "GameState.h"


void DrawUI(SDL_Renderer*& renderer, GameState& state);

void DrawHealthBar(SDL_Renderer*&, int, int, int, int, int, int);