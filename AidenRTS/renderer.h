#pragma once
class Troop;
class Building;
class CommandCenter; 

class TroopRenderer
{
public:
    void DrawHealth(Troop& TroopOBJ);
    void DrawLine(Troop TroopOBJ);
    void UpdateCircleValue(Troop& TroopOBJ);
};


class BuildingRenderer
{
public:
    void DrawHealth(Building ABuilding);
    void DrawBTexture(Building ABuilding);
    void DrawCommandCenter(CommandCenter ABuilding);
};