#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"
#include <algorithm>
#include "troops.h"







void CurrentlySelected(std::vector<Troop*>& TroopSelected, std::vector<Troop*>& TotalTroops, Vector2 mousepoint, Rectangle& sBox, int i);
Rectangle DrawSelection(Vector2& a, Vector2& b, Rectangle& Box, bool& initial, Camera2D P);
