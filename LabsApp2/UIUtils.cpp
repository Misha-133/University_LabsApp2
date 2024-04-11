#include "UIUtils.h"
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <vector>

#include "GameState.h"
#include "UiElement.h"

std::vector<UiElement*> LoadUi()
{
	std::vector<UiElement*> ui;

	//auto button = new UiElement();
	//button->X = 256;
	//button->Y = 192;
	//button->W = 128;
	//button->H = 64;
	//button->B = 3;

	//button->BackgroundColorHover = SDL_Color( 192, 255, 192, 0 );
	//button->BackgroundColorInactive = SDL_Color( 0, 128, 128, 0 );
	//button->BackgroundColorDefault = SDL_Color( 0, 0, 0, 0 );
	//button->BorderColor = SDL_Color( 255, 255, 255, 0 );
	//button->BackgroundColorPressed = SDL_Color( 64, 255, 64, 0 );
	//button->TextColor = SDL_Color( 32, 32, 255, 0 );

	//button->Text = "TestBtn";

	//ui.push_back(button);




	return ui;
}

void DrawUI(SDL_Renderer*& renderer, const GameState& state, std::vector<UiElement*>& ui)
{
	if (state.IsRunning)
	{
		DrawHealthBar(renderer, 0, 0, 192, 32, state.PlayerOneHP, state.PlayerOne->HP);
		DrawHealthBar(renderer, 448, 0, 192, 32, state.PlayerTwoHP, state.PlayerTwo->HP);

		DrawEnergyBar(renderer, 0, 40, 192, 32, state.PlayerOneEnergy, state.PlayerOne->Energy);
		DrawEnergyBar(renderer, 448, 40, 192, 32, state.PlayerTwoEnergy, state.PlayerTwo->Energy);

		if (state.CurrentMenu == GameMenu_AttackSelection)
		{
			DrawAttackSelect(renderer, state, state.FirstPlayer ? state.PlayerOne : state.PlayerTwo);
		}

		for (auto element : ui)
		{
			element->Draw(renderer);
		}
	}
}

void DrawAttackSelect(SDL_Renderer*& renderer, const GameState& state, Pokemon* pokemon)
{
	auto x = 32;
	auto y = 384;
	auto w = 576;
	auto h = 64;
	auto h1 = h / 2;
	auto y2 = y + h1;

	auto border = 2;

	auto rect = SDL_Rect(x, y, w, h);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(renderer, &rect);

	rect = SDL_Rect(x + border, y + border, w - border * 2, h - border * 2);
	SDL_SetRenderDrawColor(renderer, 128, 128,128, 0);
	SDL_RenderFillRect(renderer, &rect);

	SDL_Color color;
	color = state.MenuItem == 0 ? SDL_Color(32, 32, 255, 0) : SDL_Color(96, 96, 192, 0);
	auto str = pokemon->AttackOneName + "     D: " + std::to_string(pokemon->AttackOneDamage) + "     E: " + std::to_string(pokemon->AttackOneEnergy);
	DrawTextCentered(renderer, str, x, y, w, h1, color);

	color = state.MenuItem == 1 ? SDL_Color(32, 32, 255, 0) : SDL_Color(96, 96, 192, 0);
	str = pokemon->AttackTwoName + "     D: " + std::to_string(pokemon->AttackTwoDamage) + "     E: " + std::to_string(pokemon->AttackTwoEnergy);
	DrawTextCentered(renderer, str, x, y2, w, h1, color);
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

void DrawEnergyBar(SDL_Renderer*& renderer, int x, int y, int w, int h, unsigned int value, unsigned int total)
{
	auto rect = SDL_Rect(x, y, w, h);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(renderer, &rect);

	const float percent = (value / (float)total);
	const int width = percent * (w - 4);

	rect = SDL_Rect(x + 2, y + 2, width, h - 4);
	SDL_SetRenderDrawColor(renderer, 32, 228 * (1 - percent), 16 + 228 * percent, 0);
	SDL_RenderFillRect(renderer, &rect);

	auto hpColor = SDL_Color(255 - 192 * percent, 192 - 64 * percent, 64 + 190 * percent, 0);

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