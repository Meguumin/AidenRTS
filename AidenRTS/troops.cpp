#include "troops.h"
#include "troopselection.h"
#include "buildings.h"
# define M_PI           3.14159265358979323846  
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

Vector2 GetOffsetOfSquare(Vector2 leaderTarget, float formationSize, int size)
{
    Vector2 out = { 0 };

    int row = size / formationSize;
    int col = size % int(formationSize);
    float offsetX = (col - formationSize / 2) * 20.0f; // Adjust the spacing as needed
    float offsetY = (row - formationSize / 2) * 20.0f; // Adjust the spacing as needed
    out = { leaderTarget.x + offsetX, leaderTarget.y + offsetY };
    return out;
}

void FollowMouse(typeofmovement movement, Troop& TroopOBJ, std::vector<Troop*>& TroopSelected)
{
   
        //already done setup
        if (!TroopOBJ.isactive || TroopOBJ.isactive && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && IsUnitSelected(TroopSelected, TroopOBJ))
        {
            if (TroopOBJ.setupmovement == true)
            {
                if (movement == square)
                {
                    //try to understand this code,  Get size not based on selected, stops moving when deselected, When selected individually it moves somewhere??

                    float formationSize = std::ceil(std::sqrt(TroopSelected.size()));
                    Vector2 leaderTarget = TroopOBJ.target;


                    for (int i = 0; i < TroopSelected.size(); ++i)
                    {
                        /*
                         float deltax = TroopOBJ.target.x - SoldierSelected[i]->location.x;
                         float deltay = TroopOBJ.target.y - SoldierSelected[i]->location.y;
                         float rad = atan2(deltax, deltay);
                         float deg = rad * (180 / M_PI);
                         SoldierSelected[i]->rotation = deg;

                        */
                        TroopSelected[i]->target = GetOffsetOfSquare(leaderTarget, formationSize, i);
                        TroopSelected[i]->direction = Vector2Normalize(Vector2{ TroopSelected[i]->target.x - TroopSelected[i]->hitbox.x  ,  TroopSelected[i]->target.y - TroopSelected[i]->hitbox.y });
                    }
                }
            }
            TroopOBJ.isactive = true;
        }
    

   
    if (Vector2Distance(TroopOBJ.location, TroopOBJ.target) < 0.01f)
    {
        TroopOBJ.isactive = false;
        TroopOBJ.setupmovement = true;
    }


  TroopOBJ.location = Vector2MoveTowards(TroopOBJ.location, TroopOBJ.target, TroopOBJ.movementspeed * GetFrameTime());
     
}


void SetupTroop(int i, Building* ABuilding, std::vector<Soldier>& GridOSoldier, std::vector<Troop*>& TotalTroops, std::vector<Medic>& GridOMedic)
{
    
    switch (i) {
    case 1:
    {
        //Soldier
        Soldier newSoldier;
        newSoldier.health = 20;
        newSoldier.maxhealth = 100;
        newSoldier.movementspeed = 150;
        newSoldier.target = Vector2{ ABuilding->location.x + GetRandomValue(60, -60), ABuilding->location.y + GetRandomValue(0, -60) };
        newSoldier.location = ABuilding->location;
        newSoldier.hitbox = { ABuilding->location.x, ABuilding->location.y,15,15 };
        newSoldier.Dcolor = WHITE;
        GridOSoldier.push_back(newSoldier);
        TotalTroops.push_back(&GridOSoldier.back());
    }
        break;
    case 2:
        Medic newMedic;
        newMedic.health = 50;
        newMedic.maxhealth = 50;
        newMedic.movementspeed = 250;
        newMedic.target = Vector2{ ABuilding->location.x + GetRandomValue(60, -60), ABuilding->location.y + GetRandomValue(0, -60) };
        newMedic.location = ABuilding->location;
        newMedic.hitbox = { ABuilding->location.x, ABuilding->location.y,10,10 };
        newMedic.Dcolor = GREEN;
        GridOMedic.push_back(newMedic);
        TotalTroops.push_back(&GridOMedic.back());
        break;
    }
     
   
       
}
void Troop::DrawHealth()
{
    DrawRectangleRec(Rectangle{hitbox.x,hitbox.y - 4,hitbox.width, 2}, RED);
    DrawRectangleRec(Rectangle{ hitbox.x,hitbox.y - 4,CalculateHealthBoxWidth(), 2 }, GREEN);
 
}
float Troop::CalculateHealthBoxWidth()
{
   
    float percent = health / maxhealth;
    return Lerp(hitbox.width , hitbox.width * percent, 0.1);
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


//Make inline functions in the future
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
Vector2 CalculateEnd(Troop* troop) {
    float x = troop->location.x + troop->hitbox.width / 2 + troop->direction.x * 10;
    float y = troop->location.y + troop->hitbox.height / 2 + troop->direction.y * 10;
    return Vector2{ x, y };
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

bool UnitRepositionCheckWhileMoving(std::vector<Troop*> TroopSelected, Troop& TroopOBJ)
{
    return IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && TroopOBJ.isactive && IsUnitSelected(TroopSelected, TroopOBJ);
}


void UpdateTroopHitbox(Rectangle& r, Vector2 m) 
{
   r.x = m.x;
   r.y = m.y;
}

