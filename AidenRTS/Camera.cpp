#include "camera.h"



void UpdateCamera(Camera2D& c, Vector2& p, float& cameraspeed)
{

    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) p.y -= cameraspeed * GetFrameTime();
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) p.y += cameraspeed * GetFrameTime();
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) p.x -= cameraspeed * GetFrameTime();
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) p.x += cameraspeed * GetFrameTime();
    c.target = p;
}
void UpdateZoom(Camera2D& c)
{

    c.zoom += ((float)GetMouseWheelMove() * 0.05f);
    if (c.zoom > 3.0f) c.zoom = 3.0f;
    else if (c.zoom < 0.1f) c.zoom = 0.1f;
}