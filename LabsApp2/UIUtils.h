#pragma once
#include <SDL_render.h>

#include "GameState.h"

void DrawUI(SDL_Renderer*& renderer, const GameState& state);

void DrawAttackSelect(SDL_Renderer*& renderer, const GameState& state, Pokemon* pokemon);

void DrawHealthBar(SDL_Renderer*&, int, int, int, int, unsigned int, unsigned int);

void DrawEnergyBar(SDL_Renderer*&, int, int, int, int, unsigned int, unsigned int);

void DrawText(SDL_Renderer*& renderer, std::string& text, int& x, int& y, SDL_Color& color);

void DrawTextCentered(SDL_Renderer*& renderer, std::string& text, int& x, int& y, int& w, int& h, SDL_Color& color);

void DrawBackground(SDL_Renderer*& renderer, int w, int h);
