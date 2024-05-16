#include "GameState.h"
#include "GameLogic.h"

double damage_map[5][5] = {
{ 1.0, 1.0, 1.0, 1.5, 0.5 },
{ 1.0, 0.5, 1.0, 1.0, 1.5 },
{ 1.0, 1.0, 1.0, 1.5, 1.0 },
{ 1.5, 1.0, 1.5, 1.0, 1.0 },
{ 0.5, 1.5, 1.0, 1.0, 1.0 },
};

unsigned int get_damage(PokemonType t1, PokemonType t2, unsigned int damage)
{
	for (int i = 0; i < 5; i++)
	{
		if (t1 | (1 << i))
		{
			for (int j = 0; j < 5; j++)
			{
				if (t2 | (1 << j))
				{
					damage *= damage_map[i][j];
				}
			}
		}
	}
	return damage;
}

bool DamagePokemon(Pokemon& attacker, Pokemon& victim, int attack)
{
	if (attacker.Energy < attacker.Attacks[attack].EnergyCost)
		return false;

	unsigned int dmg = get_damage(attacker.Type, victim.Type, attacker.Attacks[attack].Damage);

	victim.HP -= dmg;
	if (victim.HP > victim.MaxHP)
		victim.HP = 0;
	attacker.Energy -= attacker.Attacks[attack].EnergyCost;

	return true;
}
