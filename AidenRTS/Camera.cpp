#include "Camera.h"



void UpdateCamera(Camera2D& c, Vector2& p)
{

    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) p.y -= 500 * GetFrameTime();
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) p.y += 500 * GetFrameTime();
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) p.x -= 500 * GetFrameTime();
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) p.x += 500 * GetFrameTime();
    c.target = p;
}
void UpdateZoom(Camera2D& c)
{

    c.zoom += ((float)GetMouseWheelMove() * 0.05f);
    if (c.zoom > 3.0f) c.zoom = 3.0f;
    else if (c.zoom < 0.1f) c.zoom = 0.1f;
}