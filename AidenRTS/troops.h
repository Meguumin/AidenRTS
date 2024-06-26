#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"
#include "misc.h"
#include <algorithm> 
#include <cmath>



class Refinery;
class Ore;

class Troop {
public:
    bool isactive = false;
    Vector2 target = { 0 };
    Vector2 location = { 0 };
    float rotation = 0;
    Vector2 direction = { 0,0 };
    float health = 0;
    float movementspeed = 200;// *getFrametime

 
};

class Soldier : public Troop {
public:
    Rectangle hitbox = { 0, 0 , 15 , 15 };
};

class Truck : public Troop {
public:
    //will change later, star to get back value
    Refinery* parentrefinery;
    enum TruckStates
    {
        IDLE = 1,
        MOVINGTOORE = 2,
        MOVINGBACK = 3,
        INITIATETIMER = 4,
        CURRENTLYMINING = 5,
        NOORES = 6
    };
    TruckStates s = IDLE;
    Ore* CurrentOreBeingMined;
    int id = 0;
;   // float moneyheld = 0;
    Rectangle hitbox = { 0, 0 , 15 , 15 };
    Timer timespentmining;
   
};

enum typeofmovement {
    relativecenter,
    random ,
    square ,
};



Vector2 GetCenterOfGroup(Soldier SoldierOBJ, std::vector<Soldier> GridOSoldier);
Vector2 GetOffsetOfSquare(Vector2 leaderTarget, float formationSize, int size);

void FollowMouse(typeofmovement movement, Soldier& SoldierOBJ, std::vector<Soldier*>& SoldierSelected);
void UpdateTroopHitbox(Rectangle& r, Vector2 m);
void SetupTroop(Troop* newTroop);
bool IsUnitSelected(std::vector<Soldier*>& SoldierSelected,Soldier& SoldierOBJ);
bool ShouldFollowMouse(std::vector<Soldier*> SoldierSelected, Soldier& SoldierOBJ);
bool EnableTarget( std::vector<Soldier*> SoldierSelected, Soldier& SoldierOBJ);
bool IsUnitStationary( std::vector<Soldier*> SoldierSelected, Soldier &SoldierOBJ);
bool UnitRepositionCheckWhileMoving( std::vector<Soldier*> SoldierSelected, Soldier& SoldierOBJ);
