#include "troops.h"
#include "troopselection.h"
# define M_PI           3.14159265358979323846  
Vector2 GetCenterOfGroup(Soldier SoldierOBJ, std::vector<Soldier> GridOSoldier)
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

void FollowMouse(typeofmovement movement, Soldier& SoldierOBJ,  std::vector<Soldier*>& SoldierSelected)
{
    
    if (!SoldierOBJ.isactive || SoldierOBJ.isactive && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && IsUnitSelected(SoldierSelected, SoldierOBJ))
    {
      
        if (movement == square )
        {
            //try to understand this code,  Get size not based on selected, stops moving when deselected, When selected individually it moves somewhere??
           
            float formationSize = std::ceil(std::sqrt(SoldierSelected.size()));
            Vector2 leaderTarget = SoldierOBJ.target;
            
            
            for (int i = 0; i < SoldierSelected.size(); ++i)
            {
               /*
                float deltax = SoldierOBJ.target.x - SoldierSelected[i]->location.x;
                float deltay = SoldierOBJ.target.y - SoldierSelected[i]->location.y;
                float rad = atan2(deltax, deltay);
                float deg = rad * (180 / M_PI);
                SoldierSelected[i]->rotation = deg;
               
               */ 
                SoldierSelected[i]->target = GetOffsetOfSquare(leaderTarget, formationSize, i);
                SoldierSelected[i]->direction = Vector2Normalize(Vector2{  SoldierSelected[i]->target.x - SoldierSelected[i]->hitbox.x  ,  SoldierSelected[i]->target.y - SoldierSelected[i]->hitbox.y});
            }
        }
        SoldierOBJ.isactive = true;
    }


    if (Vector2Distance(SoldierOBJ.location, SoldierOBJ.target) < 0.01f)
    {
        SoldierOBJ.isactive = false;
    }


  SoldierOBJ.location = Vector2MoveTowards(SoldierOBJ.location, SoldierOBJ.target, SoldierOBJ.movementspeed * GetFrameTime());
     
}


void SetupTroop(Troop* newTroop)
{
  //  newTroop->location = Barracks[0].location;
  //  newTroop->location = Vector2MoveTowards(newTroop->location, Vector2{ 100,100 }, newTroop->movementspeed * GetFrameTime());
  //  GridOSoldier.push_back(newTroop);
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
bool IsUnitSelected(std::vector<Soldier*>& SoldierSelected, Soldier& SoldierOBJ)
{
    if (std::find(SoldierSelected.begin(), SoldierSelected.end(), &SoldierOBJ) != SoldierSelected.end())
    {
        return true;
    }
    else
    {
        return false;   
    }
}

bool ShouldFollowMouse( std::vector<Soldier*> SoldierSelected, Soldier& SoldierOBJ)
{
    return IsUnitSelected(SoldierSelected, SoldierOBJ) || !IsUnitSelected(SoldierSelected, SoldierOBJ) && SoldierOBJ.isactive;
}
bool EnableTarget(std::vector<Soldier*> SoldierSelected, Soldier& SoldierOBJ)
{
    return IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || SoldierOBJ.isactive;
}
bool IsUnitStationary(std::vector<Soldier*> SoldierSelected, Soldier &SoldierOBJ)
{
    return IsUnitSelected(SoldierSelected, SoldierOBJ) && !SoldierOBJ.isactive;
}

bool UnitRepositionCheckWhileMoving(std::vector<Soldier*> SoldierSelected, Soldier& SoldierOBJ)
{
    return IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && SoldierOBJ.isactive && IsUnitSelected(SoldierSelected, SoldierOBJ);
}


void UpdateTroopHitbox(Rectangle& r, Vector2 m) 
{
   r.x = m.x;
   r.y = m.y;
}

