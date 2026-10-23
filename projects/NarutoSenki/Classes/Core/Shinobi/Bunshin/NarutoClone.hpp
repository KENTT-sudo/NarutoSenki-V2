#pragma once
#include "Hero.hpp"
#include "Kuchiyose/Kurama.hpp"
#include <cstdlib>

class NarutoClone : public Hero
{
    float _kuramaCooldown = 0;

    bool _isTransformed = false;
    std::string _originNAttackType;

    void changeAction() override
    {
        if (getName() == HeroEnum::RikudoNaruto)
            changeActionRikudo();
        else if (getName() == HeroEnum::SageNaruto)
            changeActionSage();
        else
            changeActionBase();
    }

    void resumeAction(float dt) override
    {
        if (getName() == HeroEnum::RikudoNaruto)
            resumeActionRikudo(dt);
        else if (getName() == HeroEnum::SageNaruto)
            resumeActionSage(dt);
        else
            resumeActionBase(dt);
    }

    void changeActionSage()
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

    void resumeActionSage(float dt)
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

    void changeActionRikudo()
    {
        _isTransformed = true;

        _defense += 5000;
        _isArmored = true;
        hasArmorBroken = true;
        _isOnlySkillLocked = true;

        setIdleAction(createAnimation(skillSPC4Array, 5, true, false));
        setWalkAction(createAnimation(skillSPC2Array, 10, true, false));
        setNAttackAction(createAnimation(skillSPC3Array, 10, false, true));

        setTempAttackValue1(getNAttackValue());
        setNAttackValue(560);

        setWalkSpeed(320);
        _originSpeed = 320;
    }

    void resumeActionRikudo(float dt)
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
            idle();
        }

        if (hasTempAttackValue1())
        {
            setNAttackValue(getTempAttackValue1());
            setTempAttackValue1(0);
        }
        CharacterBase::resumeAction(dt);
    }

    void changeActionBase()
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

    void resumeActionBase(float dt)
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
                case OUGIS2: enabled = _isCanOugis2 && getName() != HeroEnum::RikudoNaruto; break;
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
            if (_kuramaCooldown > 0) _kuramaCooldown -= 0.016f; // MOD: Timer countdown
            checkRetri();  // auto-use free Ramen at low HP

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

                        // MOD: Force Kurama summon once in Rikudo mode, regardless of distance
            if (getName() == HeroEnum::RikudoNaruto && _kuramaCooldown <= 0 && _isCanSkill2 && isFreeState())
            {
                changeSide(sp);
                attack(SKILL2);
                _kuramaCooldown = 30.0f;
                return;
            }

            if (abs(sp.x) > 32 || abs(sp.y) > 32)
        {
            // MOD: Rikudo Clone uses long-range skills instead of just walking
            if (getName() == HeroEnum::RikudoNaruto && isFreeState() && !_mainTarget->isTower())
            {
                if (_isCanSkill1) { changeSide(sp); attack(SKILL1); return; }
                if (_isCanSkill3) { changeSide(sp); attack(SKILL3); return; }
            }
            moveDirection = sp.getNormalized();
            walk(moveDirection);
        }
                        else
        {
            if (isFreeState())
            {
                changeSide(sp);
                if (_mainTarget->isTower())
                {
                    attack(NAttack);
                    return;
                }
                                        attackRandomSkill();
                                }
                        }

                        return;
                }

                stepOn();
        }

    Hero *createClone(int cloneTime) override
    {
        // Only Rikudo Naruto clone summons Kurama
        if (getName() != HeroEnum::RikudoNaruto)
            return nullptr;
        auto clone = createCloneHero<Kurama>(SummonEnum::Kurama);
        clone->setDEF(5000);
        clone->_isArmored = true;
        clone->setWalkSpeed(320);
        clone->_originSpeed = 320;
        clone->hasArmorBroken = true;
        return clone;
    }

};
