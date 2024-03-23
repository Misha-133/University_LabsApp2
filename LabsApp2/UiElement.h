#pragma once
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <string>

struct UiElement
{
	int X;
	int Y;
	int W;
	int H;

	int B;

	bool IsHovering;

	SDL_Color BorderColor;
	SDL_Color BackgroundColorHover;
	SDL_Color BackgroundColorInactive;
	SDL_Color BackgroundColorDefault;

	void Draw(SDL_Renderer*&);

	void HandleEvent(SDL_Event&);
	void MouseEvent(SDL_Event&);

	UiElement();
};
