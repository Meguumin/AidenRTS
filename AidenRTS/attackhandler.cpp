#include "attackhandler.h"
#include "buildings.h"
void AttackHandler::ResetAttack()
{

		isattacking = false;
		startattackanimation = false;
		attackmode = false;
		acr = 0;
		buildingattacktarget = NULL;
		troopattacktarget = NULL;
}
void AttackHandler::AttackBuilding()
{
}
void AttackHandler::AttackTroop()
{
}

void MeleeHandler::AttackBuilding()
{

    if (TimerDone(attackcircle))
    {
        if (acr > 5)
        {
            acr = 0;
            buildingattacktarget->buildinghealth -= attackdmg;
        }
        acr += 0.1f;

        StartTimer(&attackcircle, 0.03);
    }

    if (buildingattacktarget->buildinghealth < 0)
    {
        acr = 0;
        isattacking = false;
    }
}

void MeleeHandler::AttackTroop()
{
    if (TimerDone(attackcircle))
    {
        if (acr > 5)
        {
            acr = 0;
            troopattacktarget->health -= attackdmg;
        }
        acr += 0.1f;

        StartTimer(&attackcircle, 0.03);
    }
    if (troopattacktarget->health <= 0)
    {
        troopattacktarget = NULL;
        isattacking = false;
    }
}