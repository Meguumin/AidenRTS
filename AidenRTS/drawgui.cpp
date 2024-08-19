#include "drawgui.h"
#include <raylib.h>
#include "raygui.h"
#include "buildings.h"
#include "troops.h"


void drawmoneytop(int m)
{
    DrawRectangle(10, 10, 250, 113, Fade(GRAY, 0.85f));
    DrawRectangleLines(10, 10, 250, 113, BLACK);
    DrawText(TextFormat("Money: %d", m), 15, 15, 20, BLACK);
}

void Drawbuildinghighlights(int PlacementS, Vector2 GlobalMouse, Circle Range)
{
    if (CheckCircleCollisionOBJ(Range, GlobalMouse)) {
        if (PlacementS == 1)
        {
            //transparent box on mouse
            DrawRectangleV(GlobalMouse, Vector2{ 60,30 }, Fade(ORANGE, 0.3f));
        }
        if (PlacementS == 2)
        {
            DrawRectangleV(GlobalMouse, Vector2{ 40,40 }, Fade(BLUE, 0.3f));
        }
    }
}










