#include "UiElement.h"

#include <iostream>
#include <ostream>
#include <SDL_render.h>

UiElement::UiElement()
{
	X = 0;
	Y = 0;
	W = 0;
	H = 0;
	B = 0;
	IsHovering = false;
	BorderColor = { 0, 0, 0, 0 };
	BackgroundColorDefault = { 0, 0, 0, 0 };
	BackgroundColorHover = { 0, 0, 0, 0 };
	BackgroundColorInactive = { 0, 0, 0, 0 };
}

void UiElement::Draw(SDL_Renderer*& renderer)
{
	SDL_Rect rect = { X, Y, W, H };
	SDL_SetRenderDrawColor(renderer, BorderColor.r, BorderColor.g, BorderColor.b, BorderColor.a);
	SDL_RenderFillRect(renderer, &rect);

	rect = { X + B, Y + B, W - B * 2, H - B * 2 };

	if(IsHovering)
		SDL_SetRenderDrawColor(renderer, BackgroundColorHover.r, BackgroundColorHover.g, BackgroundColorHover.b, BackgroundColorHover.a);
	else
		SDL_SetRenderDrawColor(renderer, BackgroundColorDefault.r, BackgroundColorDefault.g, BackgroundColorDefault.b, BackgroundColorDefault.a);
	SDL_RenderFillRect(renderer, &rect);
}

void UiElement::MouseEvent(SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			{

			}
			break;

		case SDL_MOUSEBUTTONUP:
			{

			}
			break;

		case SDL_MOUSEMOTION:
			{
				if (event.button.x >= X && event.button.x <= X + W &&
					event.button.y >= Y && event.button.y <= Y + H)
					IsHovering = true;
				else
					IsHovering = false;
			}
		break;
	}
}


void UiElement::HandleEvent(SDL_Event& event)
{
	if (event.type == SDL_MOUSEMOTION)
		MouseEvent(event);
}
