#pragma once

enum DamageType
{
	DamageType_Fire = 0b1,
	DamageType_Ice = 0b10,
	DamageType_Lightning = 0b100,
	DamageType_Poison = 0b1000,
	DamageType_Physical = 0b10000,
	DamageType_Magic = 0b100000
};

enum GameMenu
{
	GameMenu_None = 0,
	GameMenu_AttackSelection = 1,
	GameMenu_PokemonSelection1 = 2,
	GameMenu_PokemonSelection2 = 3,
};
