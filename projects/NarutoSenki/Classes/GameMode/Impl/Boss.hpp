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
		initHeros(4, 5); // TEMP: 9 total, fits current UI
		if (getHerosArray().size() >= 5)
		{
			size_t start = getHerosArray().size() - 5;
			setHeroName(start, HeroEnum::Tsunade); // TEMP: test with known hero
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
