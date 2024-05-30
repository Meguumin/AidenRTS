#include "troopselection.h"



void Selection( Vector2 mousepoint, Rectangle& sBox, Soldier& SoldierOBJ,  std::vector<Soldier> GridOSoldier)
{

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !IsKeyDown(KEY_LEFT_SHIFT))
    {
        if (CheckCollisionPointRec(mousepoint, SoldierOBJ.hitbox))
        {
            
            SoldierOBJ.isselected = true;
        }
    }


    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionRecs(sBox, SoldierOBJ.hitbox))
        {
           
            SoldierOBJ.isselected = true;
        }
    }

}


std::vector<Soldier*> CurrentlySelected(std::vector<Soldier>& GridOSoldier)
{
    std::vector<Soldier*> outVSoldier;
    for (auto& rSoldier : GridOSoldier)
    {
        if (rSoldier.isselected)
        {
            outVSoldier.push_back(&rSoldier);
        }
    }
    
    return outVSoldier;
}

void Deselection(Vector2 mousepoint, Rectangle& sBox, Soldier& SoldierOBJ, std::vector<Soldier> GridOSoldier) {
    //Clear, Dont use for now until fixed
   


    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !IsKeyDown(KEY_LEFT_SHIFT))
    {
        if (SoldierOBJ.isselected)
        {
            if (!CheckCollisionPointRec(mousepoint, SoldierOBJ.hitbox))
            {

                SoldierOBJ.isselected = false;
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

void updateRectPostoVect()
{

}