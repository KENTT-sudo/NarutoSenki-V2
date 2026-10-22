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
		initHeros(10, 5);
		if (getHerosArray().size() >= 5)
		{
			int start = getHerosArray().size() - 5;
			setHeroName(start, HeroEnum::MadaraMusou);
			setHeroName(start + 1, HeroEnum::Itachi);
			setHeroName(start + 2, HeroEnum::Sasuke);
			setHeroName(start + 3, HeroEnum::Tobi);
			setHeroName(start + 4, HeroEnum::Pain);
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
