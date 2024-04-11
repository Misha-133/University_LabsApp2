#include "GameState.h"
#include "GameLogic.h"

void DamagePokemon(GameState& state)
{
	if (state.FirstPlayer)
	{
		if (state.MenuItem == 0)
		{
			if (state.PlayerOneEnergy >= state.PlayerOne->AttackOneEnergy)
			{
				if (state.PlayerTwoHP >= state.PlayerOne->AttackOneDamage)
				{
					state.PlayerTwoHP -= state.PlayerOne->AttackOneDamage;
				}
				else
				{
					state.PlayerTwoHP = 0;
				}
				state.PlayerOneEnergy -= state.PlayerOne->AttackOneEnergy;
			}
		}
		else
		{
			if (state.PlayerOneEnergy >= state.PlayerOne->AttackTwoEnergy)
			{
				if (state.PlayerTwoHP >= state.PlayerOne->AttackTwoDamage)
				{
					state.PlayerTwoHP -= state.PlayerOne->AttackTwoDamage;
				}
				else
				{
					state.PlayerTwoHP = 0;
				}
				state.PlayerOneEnergy -= state.PlayerOne->AttackTwoEnergy;
			}
		}
	}
	else
	{
		if (state.MenuItem == 0)
		{
			if (state.PlayerTwoEnergy >= state.PlayerTwo->AttackOneEnergy)
			{
				if (state.PlayerOneHP >= state.PlayerTwo->AttackOneDamage)
				{
					state.PlayerOneHP -= state.PlayerTwo->AttackOneDamage;
				}
				else
				{
					state.PlayerOneHP = 0;
				}
				state.PlayerTwoEnergy -= state.PlayerTwo->AttackOneEnergy;
			}
		}
		else
		{
			if (state.PlayerTwoEnergy >= state.PlayerTwo->AttackOneEnergy)
			{
				if (state.PlayerOneHP >= state.PlayerTwo->AttackOneDamage)
				{
					state.PlayerOneHP -= state.PlayerTwo->AttackOneDamage;
				}
				else
				{
					state.PlayerOneHP = 0;
				}
				state.PlayerTwoEnergy -= state.PlayerTwo->AttackOneEnergy;
			}
		}
	}
}
