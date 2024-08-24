#include "misc.h"
#include "buildings.h"
void StartTimer(Timer* timer, double lifetime)
{
    timer->startTime = GetTime();
    timer->lifeTime = lifetime;
}

bool TimerDone(Timer timer)
{
    return GetTime() - timer.startTime >= timer.lifeTime;
}

double GetElapsed(Timer timer)
{
    return GetTime() - timer.startTime;
}

Vector2 RandomVector2Location(int x, int y)
{
    return Vector2{ float(GetRandomValue(x, y)),float(GetRandomValue(x, y)) };
}

Vector2 Add2Vector2(Vector2 a, Vector2 b)
{
    return Vector2{ a.x + b.x, a.y + b.y };
}


bool CheckCircleCollisionOBJ(Circle x, Vector2 GlobalMouse)
{
    return CheckCollisionPointCircle(GlobalMouse, x.centerpos, x.radius);
}

Vector2 GetCenterPositionOfRectangle(Vector2 location, Rectangle x)
{
    return Vector2{ location.x + x.width / 2, location.y + x.height / 2 };
}

Rectangle GetRectFromPointer(Building* B)
{
    Building y = *B;
    return y.hitbox;
}

bool mousecollisionwithstate1(Vector2 location, std::vector<std::vector<Node>>& Nodelist)
{
    std::pair<short,short> buff = GetGridIndex(location);
    if (Nodelist[buff.second][buff.first].state == 0)
    {
        return false;
    }
    else {
        return true;
        }
}