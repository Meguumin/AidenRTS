#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"
#include "misc.h"
#include <algorithm> 
#include <cmath>
#include "pathfinding.h"


class Refinery;
class Ore;

class Troop {
public:
    bool isactive = false;
    Vector2 target = { 0 };

    Vector2 location = { 0 };
    Vector2 direction = { 0,0 };
    std::vector<Node*> visited;
    std::vector<Node*> path;
    std::vector<Node*> Queue;

    float rotation = 0;
    float health = 0;
    float maxhealth = 0;
    int attackdmg = 0;
    Timer attackcircle;
    float acr = 0;

    bool setupmovement = false;
    bool maintain = false;

    bool attackmode = false;
    bool isattacking = false;
    bool startattackanimation = false;

    float movementspeed = 0;
    // *getFrametime
    int indy = 0;

    short formationposition = 0;
    short groupsize = 0;
    Node* startnode;
    Node* endnode;

    Building* buildingattacktarget;

    Rectangle hitbox = { 0, 0 ,0 , 0 };
    void FindPath(std::vector<std::vector<Node>>& Nodelist);
    void Attack();
    void ResetAttack();
    void NormalizeDir();
    void DrawHealth();
    void DrawLine();
    float CalculateHealthBoxWidth();
    void ExitAnimation();
    void FindAttackPath(Vector2 GlobalMouse, std::vector<std::vector<Node>>& Nodelist, Building* ABuilding);
   
    void TroopPathINIT(Vector2 Globalmouse, std::vector<std::vector<Node>>& Nodelist);
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
bool CompareNode(const Node* p1, const Node* p2);
void FollowMouse(typeofmovement movement, Troop& TroopOBJ, std::vector<Troop*>& TroopSelected);
void UpdateTroopHitbox(Rectangle& r, Vector2 m);
void SetupTroop(int i, Building* ABuilding, std::vector<Soldier>& GridOSoldier, std::vector<Troop*>& TotalTroops, std::vector<Medic>& GridOMedic);

bool IsUnitSelected(std::vector<Troop*> TroopSelected,  Troop& TroopOBJ);
bool ShouldFollowMouse(std::vector<Troop*> TroopSelected, Troop& TroopOBJ);
bool EnableTarget(Troop& TroopOBJ);
bool IsUnitStationary(std::vector<Troop*> TroopSelected, Troop& TroopOBJ);
bool UnitRepositionCheckWhileMoving(std::vector<Troop*> TroopSelected,Troop& TroopOBJ);
