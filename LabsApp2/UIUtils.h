#pragma once
#include <SDL_render.h>

#include "GameState.h"

void draw_ui(SDL_Renderer*& renderer, GameState& state);

void draw_attack_select(SDL_Renderer*& renderer, GameState& state, Pokemon* pokemon);

void draw_health_bar(SDL_Renderer*&, int, int, int, int, unsigned int, unsigned int);

void draw_energy_bar(SDL_Renderer*&, int, int, int, int, unsigned int, unsigned int);

void draw_text(SDL_Renderer*& renderer, std::string& text, int& x, int& y, SDL_Color& color);

void draw_text_centered_small(SDL_Renderer*& renderer, std::string& text, int& x, int& y, int& w, int& h, SDL_Color& color);

void draw_text_centered_large(SDL_Renderer*& renderer, std::string& text, int& x, int& y, int& w, int& h, SDL_Color& color);

void draw_background(SDL_Renderer*& renderer, int w, int h, SDL_Texture* background_image);
