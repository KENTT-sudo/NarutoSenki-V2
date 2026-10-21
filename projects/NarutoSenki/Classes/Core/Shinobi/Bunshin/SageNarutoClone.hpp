#pragma once
#include "Hero.hpp"
#include <cstdlib>

class SageNarutoClone : public Hero
{
    bool _isTransformed = false;

    void changeAction() override
    {
        _isTransformed = true;

        _defense += 5000;
        _isArmored = true;
        hasArmorBroken = true;
        _isOnlySkillLocked = true;

        setIdleAction(createAnimation(skillSPC4Array, 5, true, false));
        setWalkAction(createAnimation(skillSPC2Array, 10, true, false));
        setNAttackAction(createAnimation(skillSPC3Array, 10, false, true));

        setWalkSpeed(320);
        _originSpeed = 320;
    }

    void resumeAction(float dt) override
    {
        _isTransformed = false;

        setIdleAction(createAnimation(idleArray, 5, true, false));
        setWalkAction(createAnimation(walkArray, 10, true, false));
        setNAttackAction(createAnimation(nattackArray, 10, false, true));

        _isOnlySkillLocked = false;

        setWalkSpeed(224);
        _originSpeed = 224;
        resetDefenseValue(5000);
        _isArmored = false;
        hasArmorBroken = false;

        if (_state != State::DEAD)
        {
            _state = State::WALK;
            setKnockDownAction(createAnimation(skillSPC5Array, 10, false, true));
            knockDown();
            setKnockDownAction(createAnimation(knockDownArray, 10, false, true));
        }

        CharacterBase::resumeAction(dt);
    }

    void attackRandomSkill()
    {
        if (_isTransformed)
        {
            attack(NAttack);
            return;
        }
        attackRandomSkillNormal();
    }

    void attackRandomSkillNormal()
    {
        ABType choices[] = {SKILL1, SKILL3, OUGIS1, OUGIS2};
        int start = std::rand() % 4;

        for (int i = 0; i < 4; ++i)
        {
            ABType type = choices[(start + i) % 4];
            bool enabled = false;

            switch (type)
            {
                case SKILL1: enabled = _isCanSkill1; break;
                case SKILL3: enabled = _isCanSkill3; break;
                case OUGIS1: enabled = _isCanOugis1; break;
                case OUGIS2: enabled = _isCanOugis2; break;
                default: break;
            }

            if (enabled)
            {
                attack(type);
                return;
            }
        }

        attack(NAttack);
    }


	void perform() override
	{
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
						attackRandomSkill();
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
					if (_isCanSkill1 && abs(sp.x) < 32)
					{
						stepBack();
						return;
					}

					changeSide(sp);
                    attackRandomSkill();
				}
				return;
			}
		}

		stepOn();
	}
};
