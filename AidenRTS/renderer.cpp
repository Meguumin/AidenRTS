#include "renderer.h"
#include "raylib.h"
#include "troops.h"
#include "buildings.h"
void TroopRenderer::DrawHealth(Troop& TroopOBJ)
{
    DrawRectangleRec(Rectangle{ TroopOBJ.hitbox.x,TroopOBJ.hitbox.y - 4,TroopOBJ.hitbox.width, 2 }, RED);
    DrawRectangleRec(Rectangle{ TroopOBJ.hitbox.x,TroopOBJ.hitbox.y - 4,TroopOBJ.CalculateHealthBoxWidth(), 2 }, GREEN);

}
void TroopRenderer::DrawLine(Troop TroopOBJ)
{
    for (int t = 0; t < TroopOBJ.PHOBJ.path.size(); ++t)
    {
        if (t + 1 < TroopOBJ.PHOBJ.path.size())
        {
            DrawLineV(Vector2{ float(TroopOBJ.PHOBJ.path[t]->xpos),float(TroopOBJ.PHOBJ.path[t]->ypos) }, Vector2{ float(TroopOBJ.PHOBJ.path[t + 1]->xpos),float(TroopOBJ.PHOBJ.path[t + 1]->ypos) }, YELLOW);
        }

    }
}

void TroopRenderer::UpdateCircleValue(Troop& TroopOBJ)
{
    if (!TroopOBJ.AHOBJ->startattackanimation)
    {
        StartTimer(&TroopOBJ.AHOBJ->attackcircle, 0.2);
        TroopOBJ.AHOBJ->startattackanimation = true;
    }


}




void BuildingRenderer::DrawCommandCenter(CommandCenter ABuilding)
{

    DrawTexture(*ABuilding.main, ABuilding.hitbox.x, ABuilding.hitbox.y, WHITE);
    DrawCircleObj(ABuilding.range, WHITE, 2);
}
void BuildingRenderer::DrawBTexture(Building ABuilding)
{
    DrawTexture(*ABuilding.main, ABuilding.hitbox.x, ABuilding.hitbox.y, WHITE);
}

void BuildingRenderer::DrawHealth(Building ABuilding)
{
    DrawRectangleRec(Rectangle{ ABuilding.hitbox.x,ABuilding.hitbox.y - 4,ABuilding.hitbox.width, 2 }, RED);
    DrawRectangleRec(Rectangle{ ABuilding.hitbox.x,ABuilding.hitbox.y - 4,ABuilding.CalculateHealthBoxWidth(), 2 }, GREEN);

}