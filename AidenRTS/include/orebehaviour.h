#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"
#include <algorithm> 
#include <cmath>
//#include "buildings.h"

class Ore 
{
public:
    bool currentlygettingmined = false;
    int type = 1;
    Rectangle Rectangle = { 0, 0, 20 ,20 };
    Vector2 OreLocation = { 0,0 };
    float randomrotation = 0;
    int ido = 0;
    double minetime = 0;
    int orehealth = 0;
};
class Building;



//Ore ReturnOreType();
void GenerateOre(std::vector<Ore>& ListOres, int amount, std::vector<Rectangle> GameMap);
//bool CheckIfAllIsMined(std::vector<Ore>& OreClusterslist);