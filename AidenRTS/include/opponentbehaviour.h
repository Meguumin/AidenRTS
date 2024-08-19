#pragma once
#include "buildings.h"
#include "troops.h"
#include "raylib.h"



struct Opponent 
{
CommandCenter base;
std::vector<Troop*> OppTotalTroops;
std::vector<Refinery> OppRefineries;
std::vector<Barrack> OppBarracks;
std::vector<Building*> OppTotalBuildings;
std::vector<Soldier> GridOppSoldier;

void initializeopp(Texture2D* texture);
void CreateOppBarracks(Texture2D* texture, std::vector<Building*>& TotalBuildings);


}extern YourNightmare;


