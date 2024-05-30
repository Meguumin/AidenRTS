#include "troops.h"
#include "troopselection.h"

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

void FollowMouse(typeofmovement movement, Soldier& SoldierOBJ, std::vector<Soldier>& GridOSoldier, std::vector<Soldier*>& SoldierSelected)
{
    
    if (!SoldierOBJ.isactive || SoldierOBJ.isactive && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && SoldierOBJ.isselected)
    {
      
        if (movement == square )
        {
            //try to understand this code,  Get size not based on selected, stops moving when deselected, When selected individually it moves somewhere??
           
            float formationSize = std::ceil(std::sqrt(SoldierSelected.size()));
            Vector2 leaderTarget = SoldierOBJ.target;
            
            
                for (int i = 0; i < SoldierSelected.size(); ++i)
                {
                    
                    int row = i / formationSize;
                    int col = i % int(formationSize);
                    float offsetX = (col - formationSize / 2) * 20.0f; // Adjust the spacing as needed
                    float offsetY = (row - formationSize / 2) * 20.0f; // Adjust the spacing as needed

          
                        SoldierSelected[i]->target.x = leaderTarget.x + offsetX;
                        SoldierSelected[i]->target.y = leaderTarget.y + offsetY;
                }
        }
        SoldierOBJ.isactive = true;
    }


    if (Vector2Distance(SoldierOBJ.location, SoldierOBJ.target) < 0.01f)
    {
        SoldierOBJ.isactive = false;
    }


  SoldierOBJ.location = Vector2MoveTowards(SoldierOBJ.location, SoldierOBJ.target, 200 * GetFrameTime());
     
}

void DrawCircleObj(Circle circle, Color color)
{
    DrawCircle(circle.centerpos.x, circle.centerpos.y, circle.radius,color);
}

void UpdateTroopHitbox(Rectangle& r, Vector2 m) 
{
   r.x = m.x;
   r.y = m.y;
}