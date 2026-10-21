#pragma once
#include "Hero.hpp"
#include <cstdlib>

class NarutoClone : public Hero
{
    bool _isTransformed = false;

    void changeAction() override
    {
        _isTransformed = true;

        setIdleAction(createAnimation(skillSPC1Array, 5, true, false));
        setWalkAction(createAnimation(skillSPC2Array, 10, true, false));
        setNAttackAction(createAnimation(skillSPC3Array, 10, false, true));
        setKnockDownAction(createAnimation(skillSPC4Array, 10, false, true));

        setWalkSpeed(320);
        _originSpeed = 320;

        _isOnlySkillLocked = true;

        setTempAttackValue1(getNAttackValue());
        setNAttackValue(960);

        _nAttackRangeX = _spcAttackRangeX3;
        _nAttackRangeY = _spcAttackRangeY3;
        _originNAttackType = _nAttackType;
        _nAttackType = _spcAttackType3;

        _defense += 5000;
        _isArmored = true;
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
        if (hasTempAttackValue1())
        {
            setNAttackValue(getTempAttackValue1());
            setTempAttackValue1(0);
        }
        hasArmorBroken = false;

        _nAttackRangeX = 16;
        _nAttackRangeY = 48;
        _nAttackType = _originNAttackType;
        resetDefenseValue(5000);
        _isArmored = false;

        if (_state != State::DEAD)
        {
            _state = State::WALK;
            knockDown();
        }

        setKnockDownAction(createAnimation(knockDownArray, 10, false, true));
        CharacterBase::resumeAction(dt);
    }

    void attackRandomSkill()
    {
        if (_isTransformed)
        {
            attack(NAttack);
            return;
        }

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
                if (notFindFlog(0))
                {
                        if (notFindHero(0))
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

                stepOn();
        }
};
