#pragma once

enum PokemonType
{
	DamageType_Fire = 1 << 0,
	DamageType_Poison = 1 << 1,
	DamageType_Magic = 1 << 2,
	DamageType_Grass = 1 << 3,
	DamageType_Water = 1 << 4,
};

enum GameMenu
{
	GameMenu_None = 0,
	GameMenu_AttackSelection = 1,
	GameMenu_PokemonSelection1 = 2,
	GameMenu_PokemonSelection2 = 3,
};
