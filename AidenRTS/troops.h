#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"
#include <algorithm> 
#include <cmath>





class Troop {
public:
    bool isselected = false;
    bool isactive = false;
    Vector2 target = { 0 };
    Vector2 location = { 0 };
    int health;
    int movementspeed;
};
class Soldier : public Troop {
public:
    Rectangle hitbox = { 0, 0 , 15 , 15 };
};


enum typeofmovement {
    relativecenter,
    random ,
    square ,
};

struct Circle {
    Vector2 centerpos;
    float radius = 2;
};

void DrawCircleObj(Circle circle, Color color);
Vector2 GetCenterOfGroup(Soldier SoldierOBJ, std::vector<Soldier> GridOSoldier);
void FollowMouse(typeofmovement movement, Soldier& SoldierOBJ,std::vector<Soldier>& GridOSoldier, std::vector<Soldier*>& SoldierSelected);
void UpdateTroopHitbox(Rectangle& r, Vector2 m);

