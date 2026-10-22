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
		if (heroDataVector.size() >= 5)
		{
			int start = heroDataVector.size() - 5;
			heroDataVector[start].name = HeroEnum::MadaraMusou;
			heroDataVector[start + 1].name = HeroEnum::Itachi;
			heroDataVector[start + 2].name = HeroEnum::Sasuke;
			heroDataVector[start + 3].name = HeroEnum::Tobi;
			heroDataVector[start + 4].name = HeroEnum::Pain;
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
