#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"
#include "misc.h"
#include <algorithm> 
#include <cmath>
#include "pathfinding.h"
#include "renderer.h"
#include "attackhandler.h"
class Refinery;
class Ore;
class Soldier;
class Medic;
class DeathHandler;



class Troop {
public:

    bool isactive = false;
    Vector2 target = { 0 };
    bool enem = false;

    
    Vector2 location = { 0 };
    Vector2 direction = { 0,0 };
 
    

    float rotation = 0;
    float health = 0;
    float maxhealth = 0;
  

    bool setupmovement = false;
    bool maintain = false;

   
    float prevhealthboxwidth = 0;
    float movementspeed = 0;
    short formationposition = 0;
    short groupsize = 0;

    GenericMovement PHOBJ;
    TroopRenderer TROBJ;
    AttackHandler* AHOBJ = nullptr;
    DeathHandler* DHOBJ = nullptr;

    Rectangle hitbox = { 0, 0 ,0 , 0 };

    void NormalizeDir();
    float CalculateHealthBoxWidth();
    void ExitAnimation();
    
    int GetAttackType();
    
  
    Color Dcolor;
    short indextotal = 0;
    short indexgrid = 0;
};

class Soldier : public Troop {
public:
    MeleeMovement MMOBJ;
    
    
};

class Medic : public Troop {

public:
};


class Truck : public Troop {
public:
    Refinery* parentrefinery; 
    Ore* CurrentOreBeingMined;
    int state = 0;
    int id = 0;
    
    
    Timer timespentmining;
    void FindOre(float previousdistance, std::vector <Ore>& ListOres);
};

enum typeofmovement {
    relativecenter,
    random ,
    square ,
};




Vector2 GetCenterOfGroup(Troop TroopOBJ, std::vector<Soldier> GridOSoldier);
Vector2 GetOffsetOfSquare(Vector2 leaderTarget, float formationSize, int size, std::vector<std::vector<Node>>& Nodelist);
Vector2 CalculateEnd(Troop* troop);
//Convert Functions from SoldierOBJ  to TroopOBJ
bool CompareNode(const Node* p1, const Node* p2);
void FollowMouse(typeofmovement movement, Troop& TroopOBJ, std::vector<Troop*>& TroopSelected, std::vector<std::vector<Node>>& Nodelist);
void UpdateTroopHitbox(Rectangle& r, Vector2 m);
void SetupTroop(int i, Building* ABuilding, std::vector<Soldier>& GridOSoldier, std::vector<Troop*>& TotalTroops, std::vector<Medic>& GridOMedic);
std::pair<bool, Troop*> MouseCollisionWithTroop(std::vector<Troop*> TroopList, Vector2 GlobalMouse);
bool IsUnitSelected(std::vector<Troop*> TroopSelected,  Troop& TroopOBJ);
bool ShouldFollowMouse(std::vector<Troop*> TroopSelected, Troop& TroopOBJ);
bool EnableTarget(Troop& TroopOBJ);
bool IsUnitStationary(std::vector<Troop*> TroopSelected, Troop& TroopOBJ);
bool UnitRepositionCheckWhileMoving(std::vector<Troop*> TroopSelected,Troop& TroopOBJ);