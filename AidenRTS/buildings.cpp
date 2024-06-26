#include "buildings.h"
#include "misc.h"
#include "raygui.h"
void ManageCreationOfBuilding(int PlacementS, Vector2 GlobalMouse, std::vector<Refinery>& Refineries, int &money, CommandCenter Top, std::vector<Barrack>& Barracks,std::vector<Building*>& TotalBuildings, std::vector<Rectangle*> Buttons)
{
    if (!CheckCollisionWithBuildings(Buttons) && money >= 500 && CheckCircleCollisionOBJ(Top.range, GlobalMouse))
    {
        switch (PlacementS) {
        case 1:
            //
            money -= 500;
            CreateNewRefinery(Refineries, GlobalMouse, TotalBuildings);
            break;
        case 2:
            money -= 300;
            CreateNewBarracks(Barracks, GlobalMouse, TotalBuildings);
            break;
        case 3:

            break;
        }
    }
}
void CreateNewRefinery( std::vector<Refinery>& Refineries, Vector2 GlobalMouse, std::vector<Building*>& TotalBuildings)
{
    Truck newTruck;


    Refineries.push_back(Refinery());
    Refinery& newRefinery = Refineries.back();



    newRefinery.location = GlobalMouse;
    newRefinery.hitbox = { 0, 0 , 60 , 30 };
    UpdateTroopHitbox(newRefinery.hitbox, newRefinery.location);

    newTruck.parentrefinery = &newRefinery;
    newTruck.location = newRefinery.location;
    UpdateTroopHitbox(newTruck.hitbox, newTruck.location);
    newRefinery.childtrucks.push_back(newTruck);

    TotalBuildings.push_back(&newRefinery);

}
void CreateNewBarracks(std::vector<Barrack>& Barracks, Vector2 GlobalMouse, std::vector<Building*>& TotalBuildings)
{
 

    Barracks.push_back(Barrack());
    Barrack& newBarrack = Barracks.back();

    newBarrack.hitbox = { 0, 0 , 40 , 40 };
    newBarrack.location = GlobalMouse;
    UpdateTroopHitbox(newBarrack.hitbox, newBarrack.location);
    TotalBuildings.push_back(&newBarrack);
}
bool CheckCollisionWithBuildings(std::vector<Rectangle*> Buttons)
{
    bool tf = false;
    for (auto &i : Buttons) {
        tf = CheckCollisionPointRec(GetMousePosition(),*i);
        if (tf == true)
        {
            return tf;
        }
    }
    return tf;
}
void Refinery::MoneyText(int i, bool &d)
{  
    if (TimerDone(MT))
    {
        
        d = false;
    }
}


void Refinery::UpdateTrucks(std::vector<Truck>& childtrucks, std::vector<Ore>& ListOres, int& money)
{
    for (int i = 0; i < childtrucks.size(); ++i)
    {
        double previousdistance = 10000;
        MoneyText(1, DT);
        childtrucks[i].direction = Vector2Normalize(Vector2{ childtrucks[i].target.x - childtrucks[i].hitbox.x  ,  childtrucks[i].target.y - childtrucks[i].hitbox.y });
        switch (childtrucks[i].s) {
        case 1:
            //IDLE
           
                for (int t = 0; t < ListOres.size(); ++t)
                {
                    
                        //doesnt work for singular ore
                        auto Distance = sqrt(pow((ListOres[t].OreLocation.x - childtrucks[i].parentrefinery->location.x), 2) + pow((ListOres[t].OreLocation.y - childtrucks[i].parentrefinery->location.y), 2));
                        if (Distance < previousdistance && !ListOres[t].currentlygettingmined)
                        {
                            previousdistance = Distance;
                            childtrucks[i].target = ListOres[t].OreLocation;
                            childtrucks[i].CurrentOreBeingMined = &ListOres[t];
                            childtrucks[i].id = ListOres[t].ido;
                        }
                    

                    if (ListOres.size() == 0)
                    {
                        //remove lists Ore clusters
                        ListOres.erase(ListOres.begin() + t);
                    }
                }
                    childtrucks[i].CurrentOreBeingMined->currentlygettingmined = true;
                    if (!(childtrucks[i].target == childtrucks[i].location))
                    {
                        childtrucks[i].s = childtrucks[i].MOVINGTOORE;
                    }
            
            break;
        case 2:
            //MOVINGTOORE
            // 100 max distance movementspeed
            childtrucks[i].location = Vector2MoveTowards(childtrucks[i].location, childtrucks[i].target, childtrucks[i].movementspeed * GetFrameTime());

            //custom bool operator in Vector2 Definition
            if (childtrucks[i].location == childtrucks[i].target)
            {
                childtrucks[i].s = childtrucks[i].INITIATETIMER;
            }
            break;
        case 3:
            //MOVINGBACK
            childtrucks[i].location = Vector2MoveTowards(childtrucks[i].location, childtrucks[i].target, childtrucks[i].movementspeed * GetFrameTime());
            //custom bool operator in Vector2 Definition
            if (childtrucks[i].location == childtrucks[i].target)
            {
                DT = true;
                StartTimer(&MT, double(0.2));
                money++;
                childtrucks[i].s = childtrucks[i].IDLE;
            }
            break;
        case 4:
            //INITIATETIMER
            //seconds
            StartTimer(&childtrucks[i].timespentmining, double(childtrucks[i].CurrentOreBeingMined->minetime));
            childtrucks[i].s = childtrucks[i].CURRENTLYMINING;

            break;
        case 5:
            //CURRENTLYMINING
 
                if (TimerDone(childtrucks[i].timespentmining))
                {

                    for (int y = 0; y < ListOres.size(); ++y)
                    {
                            if (childtrucks[i].id == ListOres[y].ido )
                            {
                                ListOres[y].Rectangle.height -= 1;
                                ListOres[y].Rectangle.width -= 1;
                                ListOres[y].orehealth--;
                                childtrucks[i].CurrentOreBeingMined->currentlygettingmined = false;
                                if (ListOres[y].orehealth == 0)
                                {
                                    ListOres.erase(ListOres.begin() + y);
                                }
                            }
                            
                           
                    }
                    childtrucks[i].target = childtrucks[i].parentrefinery->location;
                    childtrucks[i].s = childtrucks[i].MOVINGBACK;
                }
            break;
        case 6:
            // NOORES
            break;
        
        }
        UpdateTroopHitbox(childtrucks[i].hitbox, childtrucks[i].location);
    }
}
 CommandCenter CommandCenter::CreateNewCommandCenter(Vector2 GlobalMouse)
{
     CommandCenter Top;
     Top.CommandCenterPlaced = true;
     Top.location = GlobalMouse;
     Top.range.radius = 500.0;
     Top.range.centerpos = Vector2{ Top.location.x + 35, Top.location.y + 35 };
     return Top;
}

 void CommandCenter::DrawCommandCenter(CommandCenter i)
 {
     DrawRectangleV(i.location, Vector2{ 70,70 }, GREEN);
     DrawCircleObj(i.range, WHITE, 2);
 }
 void Refinery::DrawGUI()
 {

     DrawText("Refinery", 692, 15, 50, BLACK);
 }

 void Barrack::DrawGUI()
 {
     DrawText("Barrack", 696, 15, 50, BLACK);
 }