#pragma once
#include "GameMode/IGameModeHandler.hpp"

class ModeBoss : public IGameModeHandler
{
public:
	void init()
	{
		CCLOG("Enter Boss mode.");

		gd.isHardCore = false;
	}

	void onInitHeros()
    {
        // Force player team = Konoha
        forcePlayerGroup(Group::Konoha);

        // Spawn 3 players and 1 enemy
        initHeros(3, 1);

        // Force the 1 enemy to be Tsunade (for now, until Madara is fixed)
        if (getHerosArray().size() >= 4)
        {
            // The first 3 are Konoha players, the 4th is Akatsuki boss
            setHeroName(0, HeroEnum::Naruto);   // Player 1
            setHeroName(1, HeroEnum::Sasuke);   // Player 2
            setHeroName(2, HeroEnum::Sakura);   // Player 3
            setHeroName(3, HeroEnum::Tsunade);  // Enemy Boss
        }
    }

	void onGameStart()
	{
	}

	void onGameOver()
	{
	}

	void onCharacterInit(CharacterBase *c)
	{
	}

	void onCharacterDead(CharacterBase *c)
	{
	}

	void onCharacterReborn(CharacterBase *c)
	{
	}
};
