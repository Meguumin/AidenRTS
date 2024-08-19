#include "buildings.h"
#include "misc.h"
#include "raygui.h"

void ManageCreationOfBuilding(int PlacementS, Vector2 GlobalMouse, std::vector<Refinery>& Refineries, int& money, CommandCenter Top, std::vector<Barrack>& Barracks, std::vector<Building*>& TotalBuildings, std::vector<Rectangle*> Buttons, Texture2D BarrackTexture)
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
            CreateNewBarracks(Barracks, GlobalMouse, TotalBuildings, &BarrackTexture);
            break;
        case 3:

            break;
        }
    }
}

void GenerateAttackPoints(Building* ABuilding)
{
    //bottom
    ABuilding->attackpoints.push_back(Vector2{ ABuilding->location.x + ABuilding->hitbox.width /2 ,   ABuilding->location.y + ABuilding->hitbox.width });
    //top
    ABuilding->attackpoints.push_back(Vector2{ ABuilding->location.x + ABuilding->hitbox.width / 2 ,   ABuilding->location.y });
    ABuilding->attackpoints.push_back(Vector2{ ABuilding->location.x,   ABuilding->location.y + ABuilding->hitbox.width / 2 });
    ABuilding->attackpoints.push_back(Vector2{ ABuilding->location.x + ABuilding->hitbox.width,   ABuilding->location.y + ABuilding->hitbox.width / 2 });
}
void Building::DrawBTexture()
{
    DrawTexture(*main, hitbox.x, hitbox.y  , WHITE);
}
void CreateNewRefinery(std::vector<Refinery>& Refineries, Vector2 GlobalMouse, std::vector<Building*>& TotalBuildings)
{
    Truck newTruck;


    Refineries.push_back(Refinery());
    Refinery& newRefinery = Refineries.back();



    newRefinery.location = GlobalMouse;
    newRefinery.hitbox = { 0, 0 , 60 , 30 };
    newRefinery.buildinghealth = 50;
    newRefinery.buildingmaxhealth = 50;
    UpdateTroopHitbox(newRefinery.hitbox, newRefinery.location);

    newTruck.parentrefinery = &newRefinery;
    newTruck.location = newRefinery.location;
    newTruck.movementspeed = 150;
    newTruck.Dcolor = RED;
    UpdateTroopHitbox(newTruck.hitbox, newTruck.location);
    newRefinery.childtrucks.push_back(newTruck);

    TotalBuildings.push_back(&newRefinery);

}

void CreateNewBarracks(std::vector<Barrack>& Barracks, Vector2 GlobalMouse, std::vector<Building*>& TotalBuildings, Texture2D* texture)
{


    Barracks.push_back(Barrack());
    Barrack& newBarrack = Barracks.back();
    newBarrack.main = texture;
    newBarrack.buildingmaxhealth = 50;
    newBarrack.buildinghealth = 50;
    newBarrack.hitbox = { 0, 0 , float(newBarrack.main->width) , float(newBarrack.main->height) };
    newBarrack.location = GlobalMouse;
    UpdateTroopHitbox(newBarrack.hitbox, newBarrack.location);
    TotalBuildings.push_back(&newBarrack);
}

bool CheckCollisionWithBuildings(std::vector<Rectangle*> Buttons)
{
    bool tf = false;
    for (auto& i : Buttons) {
        tf = CheckCollisionPointRec(GetMousePosition(), *i);
        if (tf == true)
        {
            return tf;
        }
    }
    return tf;
}
void Refinery::MoneyText(int i, bool& d)
{
    if (TimerDone(MT))
    {

        d = false;
    }
}

void Building::DrawHealth()
{
    DrawRectangleRec(Rectangle{ hitbox.x,hitbox.y - 4,hitbox.width, 2 }, RED);
    DrawRectangleRec(Rectangle{ hitbox.x,hitbox.y - 4,CalculateHealthBoxWidth(), 2 }, GREEN);

}
float Building::CalculateHealthBoxWidth()
{
    float percent = buildinghealth / buildingmaxhealth;
    float minHealthBoxWidth = 0.0f; 
    float widthDifference = hitbox.width - minHealthBoxWidth;
    return Lerp(minHealthBoxWidth, hitbox.width, percent);
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
                    if (childtrucks[i].id == ListOres[y].ido)
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
void CommandCenter::initializeCC(Vector2 GlobalMouse, Texture2D* texture)
{
   
   main = texture;
   float halves = main->width / 2;
   buildinghealth = 500;
   buildingmaxhealth = 500;
   CommandCenterPlaced = true;
   location = GlobalMouse;
   range.radius = 500.0;
   hitbox = { location.x, location.y, float(main->width),float(main->height) };
   range.centerpos = Vector2{location.x +halves , location.y +halves };
 
   
}

void CommandCenter::DrawCommandCenter()
{
   
    DrawTexture(*main,hitbox.x, hitbox.y,  WHITE );
    DrawCircleObj(range, WHITE, 2);
}
void Refinery::DrawGUI()
{

    DrawText("Refinery", 692, 15, 50, BLACK);
}

void Barrack::DrawGUI()
{
    DrawText("Barrack", 696, 15, 50, BLACK);
}