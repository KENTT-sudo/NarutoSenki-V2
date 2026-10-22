#pragma once
#include "Hero.hpp"

class MadaraMusou : public Hero
{
    void setID(const string &name, Role role, Group group) override
    {
        Hero::setID(name, role, group);
        setScale(2.5f);  // 2.5x bigger than normal hero
    }

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
