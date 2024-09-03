#pragma once
#include "buildings.h"
#include "raylib.h"

class Troop;
class Soldier;

struct Opponent 
{
CommandCenter base;
std::vector<Troop*> OppTotalTroops;
std::vector<Soldier> GridOppSoldier;


std::vector<Refinery> OppRefineries;
std::vector<Barrack> OppBarracks;
std::vector<Building*> OppTotalBuildings;

void initializeopp(Texture2D* texture);
void CreateOppBarracks(Texture2D* texture, std::vector<Building*>& TotalBuildings);
void CreateSoldier();

}extern YourNightmare;


