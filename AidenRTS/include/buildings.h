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
    Texture2D *main;
    float buildinghealth = 0;
    float buildingmaxhealth = 0;
    std::vector<Vector2> attackpoints;
    void DrawHealth();
    void DrawBTexture();
    float CalculateHealthBoxWidth();
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
    Color BC;
    void initializeCC(Vector2 GlobalMouse, Texture2D* texture);
    void DrawCommandCenter();
};
void CreateNewRefinery( std::vector<Refinery>& Refineries, Vector2 GlobalMouse, std::vector<Building*>& TotalBuildings);

class Barrack : public Building {
public:
   void DrawGUI();

};
void CreateNewBarracks(std::vector<Barrack>& Barracks, Vector2 GlobalMouse, std::vector<Building*>& TotalBuildings, Texture2D* texture);
void GenerateAttackPoints(Building* ABuilding);
void ManageCreationOfBuilding(int PlacementS, Vector2 GlobalMouse, std::vector<Refinery>& Refineries, int& money, CommandCenter Top, std::vector<Barrack>& Barracks,std::vector<Building*>& TotalBuildings, std::vector<Rectangle*> Buttons, Texture2D BarrackTexture);
bool CheckCollisionWithBuildings(std::vector<Rectangle*> Buttons);