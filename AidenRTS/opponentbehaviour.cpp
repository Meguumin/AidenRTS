#include "opponentbehaviour.h"



void Opponent::initializeopp( Texture2D* texture)
{
     base.main = texture;
     base.buildinghealth = 500;
     base.buildingmaxhealth = 500;
     base.CommandCenterPlaced = true;
     base.location = {200, 200};
     base.hitbox = { base.location.x,  base.location.y, float(base.main->width),  float(base.main->height) };
     base.BC = RED;
     base.range.radius = 0;
     GenerateAttackPoints(&base);
     base.range.centerpos = Vector2{  base.location.x + base.main->width / 2,  base.location.y + base.main->height / 2 };
     OppTotalBuildings.push_back(&base);
     
}

void  Opponent::CreateOppBarracks(Texture2D* texture, std::vector<Building*>& TotalBuildings)
{
    OppBarracks.push_back(Barrack());
    Barrack& newBarrack = OppBarracks.back();
    newBarrack.main = texture;
    newBarrack.buildingmaxhealth = 200;
    newBarrack.buildinghealth = 200;
    newBarrack.hitbox = { 0, 0 , float(newBarrack.main->width) , float(newBarrack.main->height) };
    newBarrack.location = Add2Vector2(base.location, Vector2{100, 100});
    GenerateAttackPoints(&newBarrack);
    UpdateTroopHitbox(newBarrack.hitbox, newBarrack.location);
    OppTotalBuildings.push_back(&newBarrack);
    TotalBuildings.push_back(&newBarrack);
}

void Opponent::CreateSoldier()
{
    Soldier newSoldier;
    

    newSoldier.enem = true;
    newSoldier.health = 100;
    newSoldier.maxhealth = 100;
    newSoldier.prevhealthboxwidth = 15;
    newSoldier.movementspeed = 150; 
    newSoldier.target = Vector2{base.location.x + GetRandomValue(60, -60), base.location.y + GetRandomValue(0, -60) };
    newSoldier.location = Vector2{base.location.x + GetRandomValue(60, -60), base.location.y + GetRandomValue(0, -60) };
    newSoldier.hitbox = { newSoldier.location.x,   newSoldier.location.y,15,15 };
    newSoldier.Dcolor = RED;
    if (newSoldier.AHOBJ == NULL)
    {
        newSoldier.AHOBJ = new MeleeHandler;
    }
    //newSoldier.AHOBJ.attackdmg = 10;
    newSoldier.indextotal = OppTotalTroops.size();

    newSoldier.indexgrid = GridOppSoldier.size();
    GridOppSoldier.push_back(newSoldier);
    OppTotalTroops.push_back(&GridOppSoldier.front());
   
}