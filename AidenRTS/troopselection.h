

#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"
#include <algorithm>
#include "troops.h"






void Selection(Vector2 mousepoint, Rectangle& sBox, Soldier& SoldierOBJ, std::vector<Soldier> GridOSoldier);
void Deselection(Vector2 mousepoint, Rectangle& sBox, Soldier& SoldierOBJ,  std::vector<Soldier> GridOSoldier);
void updateRectPostoVect();
std::vector<Soldier*> CurrentlySelected(std::vector<Soldier>& GridOSoldier);
Rectangle DrawSelection(Vector2& a, Vector2& b, Rectangle& Box, bool& initial, Camera2D P);
