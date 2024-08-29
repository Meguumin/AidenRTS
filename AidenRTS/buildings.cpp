#include "buildings.h"
#include "misc.h"
#include "raygui.h"

void ManageCreationOfBuilding(int PlacementS, Vector2 GlobalMouse, std::vector<Refinery>& Refineries, int& money, CommandCenter Top, std::vector<Barrack>& Barracks, std::vector<Building*>& TotalBuildings, std::vector<Rectangle*> Buttons, Texture2D BarrackTexture, std::vector<Building*>& FriendlyBuildings, std::vector<PowerPlant>& PowerPlants, Texture2D PowerPlantTexture)
{
    if (!CheckCollisionWithBuildings(Buttons) && money >= 500 && CheckCircleCollisionOBJ(Top.range, GlobalMouse))
    {
        switch (PlacementS) {
        case 1:
            //
            money -= 500;
            CreateNewRefinery(Refineries, GlobalMouse, TotalBuildings,FriendlyBuildings);
            break;
        case 2:
            money -= 300;
            CreateNewBarracks(Barracks, GlobalMouse, TotalBuildings, &BarrackTexture, FriendlyBuildings);
            break;
        case 3:
            CreateNewPowerPlant(PowerPlants, GlobalMouse,TotalBuildings,&PowerPlantTexture,FriendlyBuildings);
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
void CreateNewRefinery(std::vector<Refinery>& Refineries, Vector2 GlobalMouse, std::vector<Building*>& TotalBuildings,  std::vector<Building*>& FriendlyBuildings)
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
    newTruck.hitbox = { 0,0,15,15 };
   // newTruck.hitbox = { 0, 0 , 60 , 30 };
    newTruck.Dcolor = RED;
    UpdateTroopHitbox(newTruck.hitbox, newTruck.location);
    newRefinery.childtrucks.push_back(newTruck);

    TotalBuildings.push_back(&newRefinery);
    FriendlyBuildings.push_back(&newRefinery);
}
void CreateNewPowerPlant(std::vector<PowerPlant>& PowerPlants, Vector2 GlobalMouse, std::vector<Building*>& TotalBuildings, Texture2D* texture, std::vector<Building*>& FriendlyBuildings)
{
    PowerPlants.push_back(PowerPlant());
    PowerPlant& newPowerPlant = PowerPlants.back();
    newPowerPlant.main = texture;
    newPowerPlant.buildingmaxhealth = 200;
    newPowerPlant.buildinghealth = 200;
    newPowerPlant.hitbox = { 0, 0 , float(newPowerPlant.main->width) , float(newPowerPlant.main->height) };
    newPowerPlant.location = GlobalMouse;
    UpdateTroopHitbox(newPowerPlant.hitbox, newPowerPlant.location);
    TotalBuildings.push_back(&newPowerPlant);
    FriendlyBuildings.push_back(&newPowerPlant);
}
void CreateNewBarracks(std::vector<Barrack>& Barracks, Vector2 GlobalMouse, std::vector<Building*>& TotalBuildings, Texture2D* texture, std::vector<Building*>& FriendlyBuildings)
{


    Barracks.push_back(Barrack());
    Barrack& newBarrack = Barracks.back();
    newBarrack.main = texture;
    newBarrack.buildingmaxhealth = 200;
    newBarrack.buildinghealth = 200;
    newBarrack.hitbox = { 0, 0 , float(newBarrack.main->width) , float(newBarrack.main->height) };
    newBarrack.location = GlobalMouse;
    UpdateTroopHitbox(newBarrack.hitbox, newBarrack.location);
    TotalBuildings.push_back(&newBarrack);
    FriendlyBuildings.push_back(&newBarrack);
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
void Refinery::MoneyText( bool& d)
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

void Truck::FindOre(float previousdistance, std::vector <Ore>& ListOres) {
    for (int t = 0; t < ListOres.size(); ++t)
    {
        auto Distance = sqrt(pow((ListOres[t].OreLocation.x - parentrefinery->location.x), 2) + pow((ListOres[t].OreLocation.y - parentrefinery->location.y), 2));
        if (Distance < previousdistance && !ListOres[t].currentlygettingmined)
        {
            previousdistance = Distance;
           CurrentOreBeingMined = &ListOres[t];
           id = ListOres[t].ido;
        }

        if (ListOres.size() < 0)
        {
            //remove lists Ore clusters
            ListOres.erase(ListOres.begin() + t);
        }
    }
}

void Refinery::UpdateTrucks(std::vector<Truck>& childtrucks, std::vector<Ore>& ListOres, int& money, std::vector<std::vector<Node>>& Nodelist)
{
    //Breaks when more than one truck
    //breaks when refinery is placed on top of ore, need to fix
    // breaks when ore is on another building causing to break?
    //end node seems to be getting set to state 1? thats why it gets stuck
    //fix moneytext
    for (int i = 0; i < childtrucks.size(); ++i)
    {
           
              childtrucks[i].NormalizeDir();
           // childtrucks[i].direction = Vector2Normalize(Vector2{ childtrucks[i].target.x - childtrucks[i].hitbox.x, childtrucks[i].target.y - childtrucks[i].hitbox.y});
             MoneyText(DT);
          
            
            if (childtrucks[i].state == 0)
            {
                //idle
                childtrucks[i].FindOre(10000000, ListOres);
                childtrucks[i].CurrentOreBeingMined->currentlygettingmined = true;
                childtrucks[i].TroopPathINIT(childtrucks[i].CurrentOreBeingMined->OreLocation, Nodelist);
                childtrucks[i].state = 1;
            }

            if (childtrucks[i].state == 1)
            {
                //go to ore
                float result = Vector2Distance(childtrucks[i].location, childtrucks[i].target);
                if (result < 0.01f)
                {
                    childtrucks[i].indy++;
                }
               
                childtrucks[i].target = Vector2{ float(childtrucks[i].path[childtrucks[i].indy]->xpos) , float(childtrucks[i].path[childtrucks[i].indy]->ypos) };

                
               
                childtrucks[i].location = Vector2MoveTowards(childtrucks[i].location, childtrucks[i].target, childtrucks[i].movementspeed * GetFrameTime());
                if (childtrucks[i].endnode == childtrucks[i].path[childtrucks[i].indy])
                {
                    childtrucks[i].isactive = false;
                    childtrucks[i].indy = 0;
                    childtrucks[i].path.clear();
                    childtrucks[i].state = 2;
                    break;
                }
            }

            if (childtrucks[i].state == 2)
            {
                //go back
                if (childtrucks[i].timespentmining.lifeTime <= 0)
                {
                    StartTimer(&childtrucks[i].timespentmining, double(childtrucks[i].CurrentOreBeingMined->minetime));
                }
                

                if (TimerDone(childtrucks[i].timespentmining))
                {
                    childtrucks[i].TroopPathINIT(childtrucks[i].parentrefinery->location, Nodelist);
                    childtrucks[i].state = 3;
                    childtrucks[i].timespentmining.lifeTime = 0;
                    for (int y = 0; y < ListOres.size(); ++y)
                    {
                        if (childtrucks[i].id == ListOres[y].ido)
                        {
                            ListOres[y].Rectangle.height -= 1;
                            ListOres[y].Rectangle.width -= 1;
                            ListOres[y].orehealth--;
                            ListOres[y].currentlygettingmined = false;
                            if (ListOres[y].orehealth < 0)
                            {
                                ListOres.erase(ListOres.begin() + y);
                            }
                        }
                    }
                }



            }

            if (childtrucks[i].state == 3)
            {
                float result = Vector2Distance(childtrucks[i].location, childtrucks[i].target);
                if (result < 0.01f)
                {
                    childtrucks[i].indy++;
                }

                childtrucks[i].target = Vector2{ float(childtrucks[i].path[childtrucks[i].indy]->xpos) , float(childtrucks[i].path[childtrucks[i].indy]->ypos) };



                childtrucks[i].location = Vector2MoveTowards(childtrucks[i].location, childtrucks[i].target, childtrucks[i].movementspeed * GetFrameTime());
                if (childtrucks[i].endnode == childtrucks[i].path[childtrucks[i].indy])
                {
                    money++;
                    //StartTimer(&MT, 0.01);
                    childtrucks[i].isactive = false;
                    childtrucks[i].indy = 0;
                    childtrucks[i].path.clear();
                    childtrucks[i].state = 0;
                    break;
                }
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
bool CheckCollsionMousewithFriendlyBuildings(Vector2 location, std::vector<Building*>& TotalBuildings)
{
    for (auto i : TotalBuildings)
    {
        if (CheckCollisionPointRec(location, i->hitbox))
        {
            return true;
        }
    }
    return false;
}