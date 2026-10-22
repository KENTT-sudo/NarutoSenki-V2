#pragma once
#include "Hero.hpp"

class Slug : public Hero
{
	void perform() override
	{
		// 1. Find follow target (Tsunade, else nearest allied hero)
		CharacterBase *followTarget = nullptr;
		if (_master && _master->_state != State::DEAD)
			followTarget = _master;
		else
		{
			float bestDist = 999999;
			for (auto hero : getGameLayer()->_CharacterArray)
			{
				if (hero == this || hero->_state == State::DEAD) continue;
				if (hero->getGroup() != getGroup()) continue;
				if (hero->isFlog() || hero->isTower()) continue;
				float d = (hero->getPosition() - getPosition()).length();
				if (d < bestDist) { bestDist = d; followTarget = hero; }
			}
		}

		if (!followTarget) { stepOn(); return; }

		// 2. Walk toward follow target
		Vec2 sp = followTarget->getPosition() - getPosition();
		if (abs(sp.x) > 64 || abs(sp.y) > 32)
		{
			walk(sp.getNormalized());
			return;
		}

		// 3. Heal if any nearby ally < 80% HP
		if (isFreeState() && _isCanSkill2)
		{
			bool shouldHeal = false;
			for (auto hero : getGameLayer()->_CharacterArray)
			{
				if (hero->_state == State::DEAD || hero->getGroup() != getGroup()) continue;
				if (!hero->isPlayerOrCom()) continue;
				Vec2 d = hero->getPosition() - getPosition();
				if (abs(d.x) <= 128 && abs(d.y) <= 128 && hero->getHpPercent() < 0.8f)
				{
					shouldHeal = true;
					break;
				}
			}
			if (shouldHeal)
			{
				attack(SKILL2);
				scheduleOnce(schedule_selector(CharacterBase::enableSkill2), _sAttackCD2);
				return;
			}
		}

		// 4. Wander
		stepOn();
	}
};
