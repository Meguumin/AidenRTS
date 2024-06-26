#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"
#include <algorithm> 
#include <cmath>

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




//Ore ReturnOreType();
void GenerateOre(std::vector<Ore>& ListOres, int amount);
//bool CheckIfAllIsMined(std::vector<Ore>& OreClusterslist);