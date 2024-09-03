#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"
#include <algorithm> 
#include <cmath>
#include "orebehaviour.h"
#include "troops.h"
#include "renderer.h"

class Building{
public:
    
    
    virtual void DrawGUI() { printf("T"); };
    Rectangle hitbox = { 0, 0 , 0 , 0 };
    Vector2 location = {0};
    Texture2D *main;
    float buildinghealth = 0;
    float buildingmaxhealth = 0;
    std::vector<Vector2> attackpoints;
    BuildingRenderer BROBJ;
    float CalculateHealthBoxWidth();
    void SetNodes(std::vector<std::vector<Node>>& Nodelist);
};

class Refinery: public Building {
public:
    std::vector<Truck> childtrucks;
    Timer MT;
    void UpdateTrucks(std::vector<Truck>& childtrucks, std::vector<Ore>& ListOres, int& money, std::vector<std::vector<Node>>& Nodelist);
    void MoneyText( bool& d);
    bool MoneyAnimCheck = false;
    void DrawGUI();
};

class PowerPlant : public Building 
{
public:
    int power = 5;
};

class CommandCenter : public Building {
public:
    bool CommandCenterPlaced = false;
    Circle range;
    Color BC;
    void initializeCC(Vector2 GlobalMouse, Texture2D* texture);
    
};

class Barrack : public Building {
public:
   void DrawGUI();

};


void CreateNewRefinery(std::vector<Refinery>& Refineries, Vector2 GlobalMouse, std::vector<Building*>& TotalBuildings, std::vector<Building*>& FriendlyBuildings);
void CreateNewPowerPlant(std::vector<PowerPlant>& PowerPlants, Vector2 GlobalMouse, std::vector<Building*>& TotalBuildings, Texture2D* texture, std::vector<Building*>& FriendlyBuildings);
void CreateNewBarracks(std::vector<Barrack>& Barracks, Vector2 GlobalMouse, std::vector<Building*>& TotalBuildings, Texture2D* texture,std::vector<Building*>& FriendlyBuildings);
void GenerateAttackPoints(Building* ABuilding);
void ManageCreationOfBuilding(int PlacementS, Vector2 GlobalMouse, std::vector<Refinery>& Refineries, int& money, CommandCenter Top, std::vector<Barrack>& Barracks,std::vector<Building*>& TotalBuildings, std::vector<Rectangle*> Buttons, Texture2D BarrackTexture, std::vector<Building*>& FriendlyBuildings, std::vector<PowerPlant>& PowerPlants, Texture2D PowerPlantTexture);
bool CheckCollisionWithBuildings(std::vector<Rectangle*> Buttons);
bool CheckCollsionMousewithFriendlyBuildings(Vector2 location, std::vector<Building*>& TotalBuildings);