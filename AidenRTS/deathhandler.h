#pragma once
#include <raylib.h>
#include <vector>
#include "troops.h"

class DeathHandler
{
public:
   
};
class SoldierDeathHandler : public DeathHandler
{
    void Death(std::vector<Soldier>& GridOSoldier, std::vector<Troop*>& TotalTroops, Troop& TroopOBJ);
};
class TruckDeathHandler : public DeathHandler
{
    void Death();
};
class MedicDeathHandler : public DeathHandler
{
    void Death();
};
class BuildingDeathHandler : public DeathHandler
{
    void Death();
};