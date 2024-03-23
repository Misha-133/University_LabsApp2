#pragma once
#include <SDL_render.h>
#include <vector>

#include "GameState.h"
#include "UiElement.h"

std::vector<UiElement*> LoadUi();

void DrawUI(SDL_Renderer*& renderer, const GameState& state, std::vector<UiElement*>& ui);

void DrawHealthBar(SDL_Renderer*&, int, int, int, int, unsigned int, unsigned int);

void DrawBackground(SDL_Renderer*& renderer, const int& w, const int& h);
