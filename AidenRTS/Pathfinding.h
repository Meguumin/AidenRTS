#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"
#include <algorithm> 

class UltraRect { 
public:  
    Rectangle Box = { 0, 0 , 10 , 10 };
    int state = 0;
    bool visited = false;
    Vector2 SelfXY = { 0,0 };
    Vector2 ParentXY = { 0,0 };

    UltraRect(float x, float y) {
        SelfXY = {x,y};
        Box.x = x;
        Box.y = y;
    }
};


void GenerateCells(std::vector<UltraRect>& Grid);
