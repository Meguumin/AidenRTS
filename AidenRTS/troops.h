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
    float maxhealth = 0;
    bool setupmovement = false;
    float movementspeed = 0;// *getFrametime
    Rectangle hitbox = { 0, 0 ,0 , 0 };
    void DrawHealth();
    float CalculateHealthBoxWidth();
    Color Dcolor;
};

class Soldier : public Troop {
public:
};
class Medic : public Troop {
public:
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



Vector2 GetCenterOfGroup(Troop TroopOBJ, std::vector<Soldier> GridOSoldier);
Vector2 GetOffsetOfSquare(Vector2 leaderTarget, float formationSize, int size);
Vector2 CalculateEnd(Troop* troop);
//Convert Functions from SoldierOBJ  to TroopOBJ
void FollowMouse(typeofmovement movement, Troop& TroopOBJ, std::vector<Troop*>& TroopSelected);
void UpdateTroopHitbox(Rectangle& r, Vector2 m);
void SetupTroop(int i, Building* ABuilding, std::vector<Soldier>& GridOSoldier, std::vector<Troop*>& TotalTroops, std::vector<Medic>& GridOMedic);
bool IsUnitSelected(std::vector<Troop*> TroopSelected,  Troop& TroopOBJ);
bool ShouldFollowMouse(std::vector<Troop*> TroopSelected, Troop& TroopOBJ);
bool EnableTarget(Troop& TroopOBJ);
bool IsUnitStationary(std::vector<Troop*> TroopSelected, Troop& TroopOBJ);
bool UnitRepositionCheckWhileMoving(std::vector<Troop*> TroopSelected,Troop& TroopOBJ);
