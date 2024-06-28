#include "troopselection.h"



// memory issue have to switch out vector for list
void CurrentlySelected(std::vector<Troop*>& TroopSelected, std::vector<Troop*>& TotalTroops, Vector2 mousepoint, Rectangle& sBox, int i)
{
  
  
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_SHIFT) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (CheckCollisionPointRec(mousepoint, TotalTroops[i]->hitbox))
            {
                // & makes it a pointer
                TroopSelected.push_back(TotalTroops[i]);
            }
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionRecs(sBox, TotalTroops[i]->hitbox) && sBox.height > 10 && sBox.width > 10)
        {
            TroopSelected.push_back(TotalTroops[i]);
        }

    

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !IsKeyDown(KEY_LEFT_SHIFT))
        {
           if (std::find(TroopSelected.begin(), TroopSelected.end(), TotalTroops[i]) != TroopSelected.end())
            {
                if (!CheckCollisionPointRec(mousepoint, TotalTroops[i]->hitbox))
                {
               TroopSelected.erase(std::remove(TroopSelected.begin(), TroopSelected.end(), TotalTroops[i]), TroopSelected.end());
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

