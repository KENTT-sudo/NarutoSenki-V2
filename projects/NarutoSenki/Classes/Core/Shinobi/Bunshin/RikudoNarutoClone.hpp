#pragma once
#include "Hero.hpp"
#include "Kuchiyose/Kurama.hpp"

class RikudoNarutoClone : public Hero
{
	float _kuramaCooldown = 0;

	void perform() override
	{
		checkRetri();  // auto-use free Ramen at low HP

		_kuramaCooldown -= 0.1f;
		if (_kuramaCooldown < 0) _kuramaCooldown = 0;

		if (notFindHero(0))
		{
			if (notFindFlog(0))
			{
				if (notFindTower(0))
				{
					_mainTarget = nullptr;
				}
			}
		}

		if (_mainTarget)
		{
			Vec2 moveDirection;
			Vec2 sp = getDistanceToTarget();

			// Auto-summon Kurama via Skill 5 (30s cooldown, permanent Kurama via Skill 2)
			if (_kuramaCooldown <= 0 && !_isControlled && !_isArmored && getGameLayer()->_isOugis2Game
				&& !_mainTarget->isTower() && !_mainTarget->isFlog() && abs(sp.x) < 128)
			{
				if (_isCanSkill2)
				{
					changeSide(sp);
					attack(SKILL2);
					_kuramaCooldown = 30.0f;
					return;
				}
				else if (_isCanOugis2)
				{
					changeSide(sp);
					attack(OUGIS2);
					_kuramaCooldown = 30.0f;
					return;
				}
			}

			if (_mainTarget->isTower() ||
				_mainTarget->isFlog())
			{
				if (abs(sp.x) > 32 || abs(sp.y) > 32)
				{
					moveDirection = sp.getNormalized();
					walk(moveDirection);
				}
				else
				{
					if (isFreeState())
					{
						changeSide(sp);
						attack(NAttack);
					}
				}
				return;
			}
			else
			{
				if (abs(sp.x) > 128 || abs(sp.y) > 16)
				{
					moveDirection = sp.getNormalized();
					walk(moveDirection);
					return;
				}
				else if ((abs(sp.x) > 48 || abs(sp.y) > 8) && !_isCanSkill1)
				{
					moveDirection = sp.getNormalized();
					walk(moveDirection);
					return;
				}
				else if (isFreeState())
				{
					if (_isCanSkill1 && _mainTarget->getDEF() < 5000)
					{
						changeSide(sp);
						attack(SKILL1);
					}
					else
					{
						changeSide(sp);
						attack(NAttack);
					}
				}
				return;
			}
		}

		stepOn();
	}

    Hero *createClone(int cloneTime) override
    {
        auto clone = createCloneHero<Kurama>(SummonEnum::Kurama);
        clone->setDEF(5000);
        clone->_isArmored = true;
        clone->setWalkSpeed(320);
        clone->_originSpeed = 320;
        clone->hasArmorBroken = true;
        return clone;
    }

};
