#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"
#include <algorithm> 
#include <queue>

class UltraRect { 
public:  
    Rectangle Box = { 0, 0 , 10 , 10 };
    int state = 0;
    bool visited = false;
    Vector2 SelfXY = { 0,0 };
    Vector2 ParentXY = { 0,0 };
    Color VisColor = GRAY;
    float h_val = 0;
    UltraRect(float x, float y) {
        SelfXY = {x,y};
        Box.x = x;
        Box.y = y;
    }
};


void GenerateCells(std::vector<std::vector<UltraRect>>& Grid, std::priority_queue<UltraRect*>& UR_priority,int col, int row);
void CalcH(std::vector<std::vector<UltraRect>> Grid, UltraRect* end,  int col, int row);

