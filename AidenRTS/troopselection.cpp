#include "troopselection.h"



// memory issue have to switch out vector for list
void CurrentlySelected(std::vector<Soldier*>& SoldierSelected,std::vector<Soldier>& GridOSoldier, Vector2 mousepoint, Rectangle& sBox, int i)
{
  

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_SHIFT) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (CheckCollisionPointRec(mousepoint, GridOSoldier[i].hitbox))
            {
                // & makes it a pointer
                SoldierSelected.push_back(&GridOSoldier[i]);
            }
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionRecs(sBox, GridOSoldier[i].hitbox) && sBox.height > 10 && sBox.width > 10)
        {
                SoldierSelected.push_back(&GridOSoldier[i]);
        }

    

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !IsKeyDown(KEY_LEFT_SHIFT))
        {
           if (std::find(SoldierSelected.begin(), SoldierSelected.end(), &GridOSoldier[i]) != SoldierSelected.end())
            {
                if (!CheckCollisionPointRec(mousepoint, GridOSoldier[i].hitbox))
                {
                    SoldierSelected.erase(std::remove(SoldierSelected.begin(), SoldierSelected.end(), &GridOSoldier[i]), SoldierSelected.end());
                }
            }

        }
   
    
}



Rectangle DrawSelection(Vector2& a, Vector2& b, Rectangle& box, bool& initial, Camera2D P)
{
    // a is start, b is end


    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        if (!initial)
        {
            a = GetScreenToWorld2D(GetMousePosition(), P);
            initial = true;
        }
        b = GetScreenToWorld2D(GetMousePosition(), P);
        Vector2 P = { std::min(a.x,b.x),std::min(a.y,b.y) };
        Vector2 T = { std::max(a.x,b.x),std::max(a.y,b.y) };
        box = { P.x, P.y, T.x - P.x, T.y - P.y };
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        box = { 0 };
        initial = false;
    }


    return box;
}

