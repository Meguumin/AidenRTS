#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"
#include <algorithm> 
#include <cmath>
class Building;
typedef struct Timer {
    double startTime;   // Start time (seconds)
    double lifeTime;    // Lifetime (seconds)
} Timer;

 struct Circle {
    Vector2 centerpos = {0};
    float radius = 2;
};

void DrawCircleObj(Circle x, Color color, int i);
bool CheckCircleCollisionOBJ(Circle x,Vector2 GlobalMouse);
void StartTimer(Timer* timer, double lifetime);
bool TimerDone(Timer timer);
Rectangle GetRectFromPointer(Building* B);

double GetElapsed(Timer timer);

Vector2 RandomVector2Location(int x, int y);
Vector2 Add2Vector2(Vector2 a, Vector2 b);
Vector2 GetCenterPositionOfRectangle(Vector2 location, Rectangle x);
