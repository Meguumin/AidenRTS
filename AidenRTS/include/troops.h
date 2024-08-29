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
class Soldier;
class Medic;

class Troop {
public:
    bool isactive = false;
    Vector2 target = { 0 };

    bool enem = false;
    virtual void FindAttackTroop();
    virtual void KillTroop();
    virtual void AttackBuilding();
    virtual void AttackTroop();
    virtual void FindAttackPathForBuilding();
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
   
    float prevhealthboxwidth = 0;
    float movementspeed = 0;
    int indy = 0;

    short formationposition = 0;
    short groupsize = 0;
    Node* startnode;
    Node* endnode;

    Troop* troopattacktarget;
    Building* buildingattacktarget;

    Rectangle hitbox = { 0, 0 ,0 , 0 };
    void FindPath(std::vector<std::vector<Node>>& Nodelist);
    void ResetAttack();
    void NormalizeDir();
    void DrawHealth();
    void DrawLine();
    float CalculateHealthBoxWidth();
    void ExitAnimation();
   
    int GetAttackType();
    
    void TroopPathINIT(Vector2 Globalmouse, std::vector<std::vector<Node>>& Nodelist);
    Color Dcolor;
};


class Soldier : public Troop {
public:
    virtual void AttackBuilding();
    virtual void AttackTroop();
    virtual void FindAttackPathForBuilding(Vector2 GlobalMouse, std::vector<std::vector<Node>>& Nodelist, Building* ABuilding);
    virtual void FindAttackTroop(std::pair<bool, Troop*> buff, std::vector<std::vector<Node>>& Nodelist);
    virtual void KillTroop(std::vector<Soldier>& GridOSoldier, std::vector<Troop*>& TotalTroops, std::vector<Troop*>& OppTotalTroops, std::vector<Soldier>& GridOppSoldier);
};
class Medic : public Troop {

public:
};


class Truck : public Troop {
public:
    //will change later, star to get back value
    Refinery* parentrefinery;
    int state = 0;
    Ore* CurrentOreBeingMined;
    int id = 0;
;   // float moneyheld = 0;
    
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