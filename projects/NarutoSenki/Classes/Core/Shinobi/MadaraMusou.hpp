#pragma once
#include "Hero.hpp"

class MadaraMusou : public Hero
{
    void perform() override
    {
        // Madara is stationary — never walks, always attacks
        if (!isFreeState())
            return;

        // Priority: Skill2 (meteor) > Skill1 (slash) > NAttack
        if (_isCanSkill2)
        {
            attack(SKILL2);
            scheduleOnce(schedule_selector(CharacterBase::enableSkill2), _sAttackCD2);
            return;
        }

        if (_isCanSkill1)
        {
            attack(SKILL1);
            scheduleOnce(schedule_selector(CharacterBase::enableSkill1), _sAttackCD1);
            return;
        }

        attack(NAttack);
    }
};
