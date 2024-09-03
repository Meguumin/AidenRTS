#pragma once
#include <raylib.h>
#include "misc.h"

//not pathfinding
class Troop;
class Building;

class AttackHandler
{
public:
    void ResetAttack();
    virtual void AttackBuilding();
    virtual void AttackTroop();
    int indy = 0;
    int attackdmg = 0;
    Timer attackcircle;
    float acr = 0;
    bool attackmode = false;
    bool isattacking = false;
    bool startattackanimation = false;
    Troop* troopattacktarget;
    Building* buildingattacktarget;

};

class MeleeHandler : public AttackHandler
{
public:
    virtual void AttackBuilding();
    virtual void AttackTroop();
};