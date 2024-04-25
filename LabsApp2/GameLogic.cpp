#include "GameState.h"
#include "GameLogic.h"

void DamagePokemon(GameState& state)
{
	if (state.FirstPlayer)
	{
		if (state.PlayerOneEnergy >= state.PlayerOne->Attacks[state.MenuItem].EnergyCost)
		{
			if (state.PlayerTwoHP >= state.PlayerOne->Attacks[state.MenuItem].Damage)
			{
				state.PlayerTwoHP -= state.PlayerOne->Attacks[state.MenuItem].Damage;
			}
			else
			{
				state.PlayerTwoHP = 0;
			}
			state.PlayerOneEnergy -= state.PlayerOne->Attacks[state.MenuItem].EnergyCost;
		}
	}
	else
	{
		if (state.PlayerTwoEnergy >= state.PlayerTwo->Attacks[state.MenuItem].EnergyCost)
		{
			if (state.PlayerOneHP >= state.PlayerTwo->Attacks[state.MenuItem].Damage)
			{
				state.PlayerOneHP -= state.PlayerTwo->Attacks[state.MenuItem].Damage;
			}
			else
			{
				state.PlayerOneHP = 0;
			}
			state.PlayerTwoEnergy -= state.PlayerTwo->Attacks[state.MenuItem].EnergyCost;
		}
	}
}
