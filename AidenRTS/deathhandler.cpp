#include "deathhandler.h"

void DeathHandler::Death()
{

}
void SoldierDeathHandler::Death(std::vector<Soldier>& GridOSoldier, std::vector<Troop*>& TotalTroops, Troop& TroopOBJ)
{
	delete TroopOBJ.AHOBJ;
	TotalTroops.erase(TotalTroops.begin() + TroopOBJ.indextotal);
	delete TroopOBJ.DHOBJ;
	GridOSoldier.erase(GridOSoldier.begin() + TroopOBJ.indexgrid);
}


void BuildingDeathHandler::Death()
{

}