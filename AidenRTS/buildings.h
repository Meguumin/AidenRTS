#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"
#include <algorithm> 
#include <cmath>
#include "orebehaviour.h"
#include "troops.h"



class Building{
public:
    virtual void DrawGUI() { printf("T"); };
    Rectangle hitbox = { 0, 0 , 0 , 0 };
    Vector2 location = {0};
};

class Refinery: public Building {
public:
    std::vector<Truck> childtrucks;
    Timer MT;
    void UpdateTrucks(std::vector<Truck>& childtrucks, std::vector<Ore>& ListOres, int& money);
    void MoneyText(int i, bool& d);
    bool DT = false;
    void DrawGUI();
};

class CommandCenter : public Building {
public:
    bool CommandCenterPlaced = false;
    Circle range;
    CommandCenter CreateNewCommandCenter(Vector2 GlobalMouse);
    void DrawCommandCenter(CommandCenter i);
};
void CreateNewRefinery( std::vector<Refinery>& Refineries, Vector2 GlobalMouse, std::vector<Building*>& TotalBuildings);

class Barrack : public Building {
public:
   void DrawGUI();

};
void CreateNewBarracks(std::vector<Barrack>& Barracks, Vector2 GlobalMouse, std::vector<Building*>& TotalBuildings);



void ManageCreationOfBuilding(int PlacementS, Vector2 GlobalMouse, std::vector<Refinery>& Refineries, int& money, CommandCenter Top, std::vector<Barrack>& Barracks,std::vector<Building*>& TotalBuildings, std::vector<Rectangle*> Buttons);
bool CheckCollisionWithBuildings(std::vector<Rectangle*> Buttons);