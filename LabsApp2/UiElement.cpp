#include "UiElement.h"

#include <iostream>
#include <ostream>
#include <SDL_render.h>
#include <SDL_ttf.h>

#include "UIUtils.h"

UiElement::UiElement()
{
	X = 0;
	Y = 0;
	W = 0;
	H = 0;
	B = 0;
	IsHovering = false;
	IsPressed = false;
	IsActive = true;
	BorderColor = { 0, 0, 0, 0 };
	BackgroundColorDefault = { 0, 0, 0, 0 };
	BackgroundColorHover = { 0, 0, 0, 0 };
	BackgroundColorInactive = { 0, 0, 0, 0 };
	BackgroundColorPressed = { 0, 0, 0, 0 };
	TextColor = { 0, 0, 0, 0 };
	Text = "";
}

void UiElement::Draw(SDL_Renderer*& renderer)
{
	SDL_Rect rect = { X, Y, W, H };
	SDL_SetRenderDrawColor(renderer, BorderColor.r, BorderColor.g, BorderColor.b, BorderColor.a);
	SDL_RenderFillRect(renderer, &rect);

	rect = { X + B, Y + B, W - B * 2, H - B * 2 };

	if(!IsActive)
		SDL_SetRenderDrawColor(renderer, BackgroundColorInactive.r, BackgroundColorInactive.g, BackgroundColorInactive.b, BackgroundColorInactive.a);
	else if (IsHovering)
	{
		if(IsPressed)
			SDL_SetRenderDrawColor(renderer, BackgroundColorPressed.r, BackgroundColorPressed.g, BackgroundColorPressed.b, BackgroundColorPressed.a);
		else
			SDL_SetRenderDrawColor(renderer, BackgroundColorHover.r, BackgroundColorHover.g, BackgroundColorHover.b, BackgroundColorHover.a);
	}
	else
		SDL_SetRenderDrawColor(renderer, BackgroundColorDefault.r, BackgroundColorDefault.g, BackgroundColorDefault.b, BackgroundColorDefault.a);

	SDL_RenderFillRect(renderer, &rect);

	DrawTextCentered(renderer, Text, X, Y, W, H, TextColor);
}

void UiElement::MouseEvent(SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			{
				if (event.button.x >= X && event.button.x <= X + W &&
					event.button.y >= Y && event.button.y <= Y + H)
					IsPressed = true;
			}
			break;

		case SDL_MOUSEBUTTONUP:
			{
				IsPressed = false;
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
	if (event.type == SDL_MOUSEMOTION 
		|| event.type == SDL_MOUSEBUTTONDOWN 
		|| event.type == SDL_MOUSEBUTTONUP)
		MouseEvent(event);
}
