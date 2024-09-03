#include "troops.h"
#include "troopselection.h"
#include "buildings.h"
#include "deathhandler.h"
# define M_PI           3.14159265358979323846



void Troop::NormalizeDir()
{
   direction = Vector2Normalize(Vector2{ target.x - hitbox.x, target.y - hitbox.y });
}


void Troop::ExitAnimation()
{
    if (!setupmovement)
    {
      location = Vector2MoveTowards(location, target,movementspeed * GetFrameTime());
        if (Vector2Distance(location, target) < 0.01f)
        {
            setupmovement = true;
        }

    }
}




float Troop::CalculateHealthBoxWidth()
{
   
    float percent = health / maxhealth;
    prevhealthboxwidth = Lerp(prevhealthboxwidth, health / maxhealth * hitbox.width, 1.0f / 1000);
    return Lerp(prevhealthboxwidth, health / maxhealth * hitbox.width, 1.0f /1000);
}

int Troop::GetAttackType()
{
    if (AHOBJ->buildingattacktarget == NULL && AHOBJ->troopattacktarget == NULL)
    {
        return 0;
    }
    else if (AHOBJ->buildingattacktarget != NULL)
    {
        return 1;
    }
    else if (AHOBJ->troopattacktarget != NULL)
    {
        return 2;
    }
}





void DrawCircleObj(Circle circle, Color color, int i)
{
    if (i == 1)
    {
        DrawCircle(circle.centerpos.x, circle.centerpos.y, circle.radius, color);
    }
    if (i == 2)
    {
        DrawCircleLines(circle.centerpos.x, circle.centerpos.y, circle.radius, color);
    }
}

void FollowMouse(typeofmovement movement, Troop& TroopOBJ, std::vector<Troop*>& TroopSelected, std::vector<std::vector<Node>>& Nodelist)
{
    if (movement == square)
    {
        //try to understand this code,  Get size not based on selected, stops moving when deselected, When selected individually it moves somewhere??

        Vector2 leaderTarget = Vector2{ float(TroopOBJ.PHOBJ.path[TroopOBJ.AHOBJ->indy]->xpos) , float(TroopOBJ.PHOBJ.path[TroopOBJ.AHOBJ->indy]->ypos) };

        float result = Vector2Distance(TroopOBJ.location, TroopOBJ.target);
        if (result < 0.01f)
        {

            TroopOBJ.AHOBJ->indy++;
        }

        // 
        if (std::find(TroopSelected.begin(), TroopSelected.end(), &TroopOBJ) != TroopSelected.end())
        {
            TroopOBJ.maintain = true;
        }

        if (TroopSelected.size() >= 2 && std::find(TroopSelected.begin(), TroopSelected.end(), &TroopOBJ) != TroopSelected.end() || TroopOBJ.maintain)
        {

            TroopOBJ.target = GetOffsetOfSquare(leaderTarget, TroopOBJ.groupsize, TroopOBJ.formationposition, Nodelist);

        }


        else
        {
            TroopOBJ.target = leaderTarget;
        }



        if (TroopOBJ.PHOBJ.endnode == TroopOBJ.PHOBJ.path[TroopOBJ.AHOBJ->indy])
        {
            TroopOBJ.isactive = false;
            if (TroopOBJ.AHOBJ->attackmode)
            {
                TroopOBJ.AHOBJ->isattacking = true;
            }
            TroopOBJ.AHOBJ->indy = 0;
            TroopOBJ.PHOBJ.path.clear();
            TroopOBJ.setupmovement = true;
            TroopOBJ.maintain = false;

            TroopOBJ.formationposition = NULL;
        }




    }

    TroopOBJ.location = Vector2MoveTowards(TroopOBJ.location, TroopOBJ.target, TroopOBJ.movementspeed * GetFrameTime());

}


//Make inline functions in the future
void SetupTroop(int i, Building* ABuilding, std::vector<Soldier>& GridOSoldier, std::vector<Troop*>& TotalTroops, std::vector<Medic>& GridOMedic)
{

    switch (i) {
    case 1:
    {
        //Soldier
        Soldier newSoldier;
        newSoldier.health = 100;
        newSoldier.maxhealth = 100;
        newSoldier.movementspeed = 150;
        newSoldier.prevhealthboxwidth = 15;
        newSoldier.target = Vector2{ ABuilding->location.x + GetRandomValue(60, -60), ABuilding->location.y + GetRandomValue(0, -60) };
        newSoldier.location = ABuilding->location;
        newSoldier.hitbox = { ABuilding->location.x, ABuilding->location.y,15,15 };
        newSoldier.Dcolor = WHITE;
        //remember to delete AHOOBJ
        if (newSoldier.AHOBJ == NULL)
        {
            newSoldier.AHOBJ = new MeleeHandler;
        }
        if (newSoldier.DHOBJ == NULL)
        {
            newSoldier.DHOBJ = new SoldierDeathHandler;
        }
        newSoldier.AHOBJ->attackdmg = 10;
        //remember to delete pointer because memoryu leak
        
        newSoldier.indextotal = TotalTroops.size() + 1;

        newSoldier.indexgrid = GridOSoldier.size() + 1;
        GridOSoldier.push_back(newSoldier);

        TotalTroops.push_back(&GridOSoldier.back());
    }
    break;
    case 2:
        Medic newMedic;
        newMedic.health = 50;
        newMedic.maxhealth = 50;
        newMedic.movementspeed = 250;
        newMedic.prevhealthboxwidth = 10;
        newMedic.target = Vector2{ ABuilding->location.x + GetRandomValue(60, -60), ABuilding->location.y + GetRandomValue(0, -60) };
        newMedic.location = ABuilding->location;
        newMedic.hitbox = { ABuilding->location.x, ABuilding->location.y,10,10 };
        newMedic.Dcolor = GREEN;
        if (newMedic.AHOBJ == NULL)
        {
            newMedic.AHOBJ = new MeleeHandler;
        }
        if (newMedic.DHOBJ == NULL)
        {
            //change
            newMedic.DHOBJ = new SoldierDeathHandler;
        }
        newMedic.AHOBJ->attackdmg = 5;
        GridOMedic.push_back(newMedic);
        TotalTroops.push_back(&GridOMedic.back());
        break;
    }



}


void UpdateTroopHitbox(Rectangle& r, Vector2 m)
{
    r.x = m.x;
    r.y = m.y;
}




Vector2 CalculateEnd(Troop* troop) {
    float x = troop->location.x + troop->hitbox.width / 2 + troop->direction.x * 10;
    float y = troop->location.y + troop->hitbox.height / 2 + troop->direction.y * 10;
    return Vector2{ x, y };
}
Vector2 GetCenterOfGroup(Troop TroopOBJ, std::vector<Soldier> GridOSoldier)
{
    Vector2 total = { 0 };
    Vector2 center = { 0 };
    for (int i = 0; i < GridOSoldier.size(); ++i)
    {
        total.x += GridOSoldier[i].location.x;
        total.y += GridOSoldier[i].location.y;
    }
    //wouldnt work with multiple groups

    center.x = total.x / GridOSoldier.size();
    center.y = total.y / GridOSoldier.size();

    return center;
}

Vector2 GetOffsetOfSquare(Vector2 leaderTarget, float formationSize, int size, std::vector<std::vector<Node>>& Nodelist)
{
    Vector2 out = { 0 };

    int row = size / formationSize;
    int col = size % int(formationSize);
    float offsetX = (col - formationSize / 2) * 20.0f; // Adjust the spacing as needed
    float offsetY = (row - formationSize / 2) * 20.0f; // Adjust the spacing as needed
    std::pair<short, short> index = GetGridIndex(Vector2{ leaderTarget.x + offsetX, leaderTarget.y });
    while (Nodelist[index.second][index.first].state != 0)
    {
        offsetX += 8;
        index.second++;
    }
    out = { leaderTarget.x + offsetX, leaderTarget.y };

    return out;
}





//misc
std::pair<bool, Troop*> MouseCollisionWithTroop(std::vector<Troop*> TroopList, Vector2 GlobalMouse)
{
    std::pair<bool, Troop*> buffer;
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && !IsKeyDown(KEY_LEFT_SHIFT))
    {
        for (int i = 0; i < TroopList.size(); ++i)
        {
            if (CheckCollisionPointRec(GlobalMouse, TroopList[i]->hitbox))
            {
                buffer = {true, TroopList[i]};
                return buffer;
            }
        }
       
    }
    buffer = {false, NULL };
    return buffer;
}











bool IsUnitSelected(std::vector<Troop*> TroopSelected, Troop& TroopOBJ)
{
    if (std::find(TroopSelected.begin(), TroopSelected.end(), &TroopOBJ) != TroopSelected.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool ShouldFollowMouse(std::vector<Troop*> TroopSelected, Troop& TroopOBJ)
{
    return IsUnitSelected(TroopSelected, TroopOBJ) || !IsUnitSelected(TroopSelected, TroopOBJ) && TroopOBJ.isactive;
}
bool EnableTarget(Troop& TroopOBJ)
{
    return IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || TroopOBJ.isactive;
}
bool IsUnitStationary(std::vector<Troop*> TroopSelected, Troop& TroopOBJ)
{
    return IsUnitSelected(TroopSelected, TroopOBJ) && !TroopOBJ.isactive;
}

bool CompareNode(const Node* p1, const Node* p2)
{
    return p1->values[0] < p2->values[0];
}

bool UnitRepositionCheckWhileMoving(std::vector<Troop*> TroopSelected, Troop& TroopOBJ)
{
    return IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && TroopOBJ.isactive && IsUnitSelected(TroopSelected, TroopOBJ);
}