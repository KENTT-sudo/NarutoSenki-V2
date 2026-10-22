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
		// Force player team = Konoha (enemies will be Akatsuki)
		forcePlayerGroup(Group::Konoha);

		initHeros(3, 1); // 3v1 Boss Mode

		// Force last hero (enemy boss) = Madara
		if (getHerosArray().size() >= 1)
		{
			size_t lastIdx = getHerosArray().size() - 1;
			setHeroName(lastIdx, HeroEnum::MadaraMusou);
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
