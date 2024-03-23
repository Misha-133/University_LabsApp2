#include "UIUtils.h"
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <vector>

#include "GameState.h"
#include "UiElement.h"

std::vector<UiElement*> LoadUi()
{
	std::vector<UiElement*> ui;

	auto button = new UiElement();
	button->X = 256;
	button->Y = 192;
	button->W = 128;
	button->H = 64;
	button->B = 3;

	button->BackgroundColorHover = SDL_Color( 192, 255, 192, 0 );
	button->BackgroundColorInactive = SDL_Color( 0, 128, 128, 0 );
	button->BackgroundColorDefault = SDL_Color( 0, 0, 0, 0 );
	button->BorderColor = SDL_Color( 255, 255, 255, 0 );
	button->BackgroundColorPressed = SDL_Color( 64, 255, 64, 0 );
	button->TextColor = SDL_Color( 32, 32, 255, 0 );

	button->Text = "TestBtn";

	ui.push_back(button);


	auto button2 = new UiElement();
	button2->X = 64;
	button2->Y = 192;
	button2->W = 128;
	button2->H = 64;
	button2->B = 3;
	button2->IsActive = false;

	button2->BackgroundColorHover = SDL_Color(192, 255, 192, 0);
	button2->BackgroundColorInactive = SDL_Color(0, 128, 128, 0);
	button2->BackgroundColorDefault = SDL_Color(0, 0, 0, 0);
	button2->BorderColor = SDL_Color(255, 255, 255, 0);
	button2->BackgroundColorPressed = SDL_Color(64, 255, 64, 0);
	button2->TextColor = SDL_Color(128, 128, 255, 0);

	button2->Text = "Inactive";

	ui.push_back(button2);

	return ui;
}

void DrawUI(SDL_Renderer*& renderer, const GameState& state, std::vector<UiElement*>& ui)
{
	if (state.IsRunning)
	{
		DrawHealthBar(renderer, 0, 0, 192, 32, state.PlayerOneHP, 100);
		DrawHealthBar(renderer, 448, 0, 192, 32, state.PlayerTwoHP, 100);

		for (auto element : ui)
		{
			element->Draw(renderer);
		}
	}
}

void DrawHealthBar(SDL_Renderer*& renderer, int x, int y, int w, int h, unsigned int value, unsigned int total)
{
	auto rect = SDL_Rect(x, y, w, h);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(renderer, &rect);

	const float percent = (value / (float)total);
	const int width = percent * (w - 4);

	rect = SDL_Rect(x + 2, y + 2, width, h - 4);
	SDL_SetRenderDrawColor(renderer, 228 * (1 - percent), 16 + 228 * percent, 32, 0);
	SDL_RenderFillRect(renderer, &rect);

	auto hpColor = SDL_Color(64 + 190 * percent, 192 - 64 * percent, 255 - 192 * percent, 0);

	auto str = std::to_string(value) + "/" + std::to_string(total);

	DrawTextCentered(renderer, str, x, y, w, h, hpColor);
}

void DrawText(SDL_Renderer*& renderer, std::string& text, int& x, int& y, SDL_Color& color)
{
	static auto sans = TTF_OpenFont("data/fonts/main_font.ttf", 18);

	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(sans, text.data(), color);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect rect = { x, y, surfaceMessage->w, surfaceMessage->h };

	SDL_RenderCopy(renderer, message, nullptr, &rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

void DrawTextCentered(SDL_Renderer*& renderer, std::string& text, int& x, int& y, int& w, int& h, SDL_Color& color)
{
	static auto sans = TTF_OpenFont("data/fonts/main_font.ttf", 18);

	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(sans, text.data(), color);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect rect = { x + (w / 2) - surfaceMessage->w / 2, y + (h / 2) - surfaceMessage->h / 2, surfaceMessage->w, surfaceMessage->h};

	SDL_RenderCopy(renderer, message, nullptr, &rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

void DrawBackground(SDL_Renderer*& renderer, int w, int h)
{
	SDL_SetRenderDrawColor(renderer, 48, 48, 48, 0);
	auto backgroundRect = SDL_Rect(0, 0, w, h);
	SDL_RenderFillRect(renderer, &backgroundRect);
}