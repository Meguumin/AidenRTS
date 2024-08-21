#include "troops.h"
#include "troopselection.h"
#include "buildings.h"
# define M_PI           3.14159265358979323846  
Vector2 GetCenterOfGroup(Troop TroopOBJ, std::vector<Soldier> GridOSoldier)
{
    Vector2 total = { 0 };
    Vector2 center = { 0 };
    for (int i = 0; i < GridOSoldier.size(); ++i)
    {
        total.x += GridOSoldier[i].location.x;
        total.y += GridOSoldier[i].location.y;
    }
    //wouldnt work with multiple groups

    center.x = total.x / GridOSoldier.size();
    center.y = total.y / GridOSoldier.size();
    
    return center;
}

Vector2 GetOffsetOfSquare(Vector2 leaderTarget, float formationSize, int size)
{
    Vector2 out = { 0 };

    int row = size / formationSize;
    int col = size % int(formationSize);
    float offsetX = (col - formationSize / 2) * 20.0f; // Adjust the spacing as needed
    float offsetY = (row - formationSize / 2) * 20.0f; // Adjust the spacing as needed
    out = { leaderTarget.x + offsetX, leaderTarget.y};
    
    return out;
}



void Troop::NormalizeDir()
{
    direction = Vector2Normalize(Vector2{ target.x - hitbox.x  , target.y - hitbox.y });
}

void Troop::DrawLine()
{
    for (int t = 0; t <path.size(); ++t)
    {
        if (t + 1 < path.size())
        {
            DrawLineV(Vector2{ float(path[t]->xpos),float(path[t]->ypos) }, Vector2{ float(path[t + 1]->xpos),float(path[t + 1]->ypos) }, YELLOW);
        }

    }
}

void Troop::ResetAttack()
{
   isattacking = false;
   startattackanimation = false;
   attackmode = false;
   acr = 0;
   buildingattacktarget = NULL;
   troopattacktarget = NULL;
}
void Troop::ExitAnimation()
{
    if (!setupmovement)
    {
      location = Vector2MoveTowards(location, target,movementspeed * GetFrameTime());
        if (Vector2Distance(location, target) < 0.01f)
        {
            setupmovement = true;
        }

    }
}



void FollowMouse(typeofmovement movement, Troop& TroopOBJ, std::vector<Troop*>& TroopSelected)
{
         if (movement == square)
        {
                //try to understand this code,  Get size not based on selected, stops moving when deselected, When selected individually it moves somewhere??

                Vector2 leaderTarget = Vector2{ float(TroopOBJ.path[TroopOBJ.indy]->xpos) , float(TroopOBJ.path[TroopOBJ.indy]->ypos) };

                float result = Vector2Distance(TroopOBJ.location, TroopOBJ.target);
                if (result < 0.01f)
                {
                  
                    TroopOBJ.indy++;
                }

               // 
                if (std::find(TroopSelected.begin(), TroopSelected.end(), &TroopOBJ) != TroopSelected.end())
                {
                    TroopOBJ.maintain = true;
                }
                
                  if (TroopSelected.size() >= 2 && std::find(TroopSelected.begin(), TroopSelected.end(), &TroopOBJ) != TroopSelected.end() || TroopOBJ.maintain)
                    {
                   
                      TroopOBJ.target = GetOffsetOfSquare(leaderTarget,TroopOBJ.groupsize, TroopOBJ.formationposition);
     
                    }
                
              
                else 
                {
                    TroopOBJ.target = leaderTarget;
                }
                  
                  
                
                if (TroopOBJ.endnode == TroopOBJ.path[TroopOBJ.indy])
                {
                    TroopOBJ.isactive = false;
                    if(TroopOBJ.attackmode)
                    {
                        TroopOBJ.isattacking = true;
                    }
                    TroopOBJ.indy = 0;
                    TroopOBJ.path.clear();
                    TroopOBJ.setupmovement = true;
                    TroopOBJ.maintain = false;
                  
                    TroopOBJ.formationposition = NULL;
                }
            
                

   
    }

    TroopOBJ.location = Vector2MoveTowards(TroopOBJ.location, TroopOBJ.target, TroopOBJ.movementspeed * GetFrameTime());

}

bool CompareNode(const Node* p1, const Node* p2)
{
    return p1->values[0] < p2->values[0];
}

void Troop::AttackBuilding()
{
    
    if (TimerDone(attackcircle))
    {
        if (acr > 5)
        {
            acr = 0;
            buildingattacktarget->buildinghealth -= attackdmg;
        }
        acr += 0.1;
        
        StartTimer(&attackcircle, 0.03);
    }
    if (buildingattacktarget->buildinghealth < 0)
    {
        isattacking = false;
    }
}

void Troop::AttackTroop()
{
    if (TimerDone(attackcircle))
    {
        if (acr > 5)
        {
            acr = 0;
            troopattacktarget->health -= attackdmg;
        }
        acr += 0.1;

        StartTimer(&attackcircle, 0.03);
    }
    if (troopattacktarget->health <= 0)
    {
        isattacking = false;
    }
}
void Troop::FindPath(std::vector<std::vector<Node>>& Nodelist)
{  
    path.clear();
       
    
  

    while (!Queue.empty())
   {
            Node* current = Queue[0];  
            std::vector<Node*> ADJ = GetAdjCells(Nodelist, current, 1000, 1000);
            CalcGandF(current, ADJ);
            Queue.erase(Queue.begin());
            for (auto obj : ADJ)
            {
                obj->nodevisited = true;
                visited.push_back(obj);
                Queue.push_back(obj);
            }
            std::sort(Queue.begin(), Queue.end(), CompareNode);
           
            if (current == endnode)
            {
               
                while (current != startnode)
                {
                    path.insert(path.begin(), current); // Insert at the beginning
                    current = current->parent;
                   

                }

                for (auto obj : visited)
                {
                    obj->nodevisited = false;
                    obj->parent = NULL;
                    obj->multi = 1;
                }
               
                
                visited.clear();
                Queue.clear();
                break;
           }
   }
}

void Troop::TroopPathINIT(Vector2 GlobalMouse, std::vector<std::vector<Node>>& Nodelist)
{
    indy = 0;
    std::pair<short, short> pointerindex = GetGridIndex(GlobalMouse);
    std::pair<short, short> soldierindex = GetGridIndex(location);

    Queue.push_back(&Nodelist[soldierindex.second][soldierindex.first]);
    endnode = &Nodelist[pointerindex.second][pointerindex.first];
    CalcH(Nodelist, endnode, 1000, 1000);
    startnode = &Nodelist[soldierindex.second][soldierindex.first];
    if (!endnode->state == 1)
    {
        endnode->state = 0;
    }
    startnode->state = 0;
   
    FindPath(Nodelist);

    isactive = true;

}

void Troop::FindAttackPathForBuilding(Vector2 GlobalMouse, std::vector<std::vector<Node>>& Nodelist, Building* ABuilding)
{
    Vector2 temp = {0,0};
    float current = 0;
    float prev = 10000000;
    indy = 0;
    for (auto i : ABuilding->attackpoints)
    {
            
        current = Vector2Distance(i, location);
        
        if (current < prev)
        {   
            temp = i;
            prev = current;
        }
        
    }
    
    std::pair<short, short> pointerindex = GetGridIndex(temp);
    std::pair<short, short> soldierindex = GetGridIndex(location);

    Queue.push_back(&Nodelist[soldierindex.second][soldierindex.first]);
    endnode = &Nodelist[pointerindex.second][pointerindex.first];

    buildingattacktarget = ABuilding;
    CalcH(Nodelist, endnode, 1000, 1000);
    startnode = &Nodelist[soldierindex.second][soldierindex.first];
    endnode->state = 0;
    startnode->state = 0;

    
    FindPath(Nodelist);
    isactive = true;
    attackmode = true;

}

void SetupTroop(int i, Building* ABuilding, std::vector<Soldier>& GridOSoldier, std::vector<Troop*>& TotalTroops, std::vector<Medic>& GridOMedic)
{
    
    switch (i) {
    case 1:
    {
        //Soldier
        Soldier newSoldier;
        newSoldier.health = 100;
        newSoldier.maxhealth = 100;
        newSoldier.movementspeed = 150;
        newSoldier.prevhealthboxwidth = 15;
        newSoldier.target = Vector2{ ABuilding->location.x + GetRandomValue(60, -60), ABuilding->location.y + GetRandomValue(0, -60) };
        newSoldier.location = ABuilding->location;
        newSoldier.hitbox = { ABuilding->location.x, ABuilding->location.y,15,15 };
        newSoldier.Dcolor = WHITE;
        newSoldier.attackdmg = 10;
        GridOSoldier.push_back(newSoldier);
        TotalTroops.push_back(&GridOSoldier.back());
    }
        break;
    case 2:
        Medic newMedic;
        newMedic.health = 50;
        newMedic.maxhealth = 50;
        newMedic.movementspeed = 250;
        newMedic.prevhealthboxwidth = 10;
        newMedic.target = Vector2{ ABuilding->location.x + GetRandomValue(60, -60), ABuilding->location.y + GetRandomValue(0, -60) };
        newMedic.location = ABuilding->location;
        newMedic.hitbox = { ABuilding->location.x, ABuilding->location.y,10,10 };
        newMedic.Dcolor = GREEN;
        newMedic.attackdmg = 5;
        GridOMedic.push_back(newMedic);
        TotalTroops.push_back(&GridOMedic.back());
        break;
    }
     
   
       
}
void Troop::DrawHealth()
{
    DrawRectangleRec(Rectangle{hitbox.x,hitbox.y - 4,hitbox.width, 2}, RED);
    DrawRectangleRec(Rectangle{ hitbox.x,hitbox.y - 4,CalculateHealthBoxWidth(), 2 }, GREEN);
 
}
float Troop::CalculateHealthBoxWidth()
{
   
    float percent = health / maxhealth;
    prevhealthboxwidth = Lerp(prevhealthboxwidth, health / maxhealth * hitbox.width, 1.0f / 1000);
    return Lerp(prevhealthboxwidth, health / maxhealth * hitbox.width, 1.0f /1000);
}

int Troop::GetAttackType()
{
    if (buildingattacktarget == NULL && troopattacktarget == NULL)
    {
        return 0;
    }
    else if (buildingattacktarget != NULL)
    {
        return 1;
    }
    else if (troopattacktarget != NULL)
    {
        return 2;
    }
}


void Soldier::FindAttackTroop(std::pair<bool, Troop*> buff, std::vector<std::vector<Node>>& Nodelist)
{

    std::pair<short, short> enemyindex = GetGridIndex(Vector2Add(buff.second->location, Vector2{ buff.second->hitbox.width / 2, buff.second->hitbox.height / 2 }));
    std::pair<short, short> soldierindex = GetGridIndex(location);

    Queue.push_back(&Nodelist[soldierindex.second][soldierindex.first]);
    endnode = &Nodelist[enemyindex.second][enemyindex.first];

    
    CalcH(Nodelist, endnode, 1000, 1000);
    startnode = &Nodelist[soldierindex.second][soldierindex.first];
    endnode->state = 0;
    startnode->state = 0;


    FindPath(Nodelist);
    isactive = true;
    attackmode = true;

}
void Troop::FindAttackTroop()
{

}

void DrawCircleObj(Circle circle, Color color, int i)
{
    if (i == 1)
    {
        DrawCircle(circle.centerpos.x, circle.centerpos.y, circle.radius, color);
    }
    if (i == 2)
    {
        DrawCircleLines(circle.centerpos.x, circle.centerpos.y, circle.radius, color);
    }
}


//Make inline functions in the future
bool IsUnitSelected(std::vector<Troop*> TroopSelected, Troop& TroopOBJ)
{
    if (std::find(TroopSelected.begin(), TroopSelected.end(), &TroopOBJ) != TroopSelected.end())
    {
        return true;
    }
    else
    {
        return false;   
    }
}
Vector2 CalculateEnd(Troop* troop) {
    float x = troop->location.x + troop->hitbox.width / 2 + troop->direction.x * 10;
    float y = troop->location.y + troop->hitbox.height / 2 + troop->direction.y * 10;
    return Vector2{ x, y };
}
bool ShouldFollowMouse(std::vector<Troop*> TroopSelected, Troop& TroopOBJ)
{
    return IsUnitSelected(TroopSelected, TroopOBJ) || !IsUnitSelected(TroopSelected, TroopOBJ) && TroopOBJ.isactive;
}
bool EnableTarget(Troop& TroopOBJ)
{
    return IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || TroopOBJ.isactive;
}
bool IsUnitStationary(std::vector<Troop*> TroopSelected, Troop& TroopOBJ)
{
    return IsUnitSelected(TroopSelected, TroopOBJ) && !TroopOBJ.isactive;
}

bool UnitRepositionCheckWhileMoving(std::vector<Troop*> TroopSelected, Troop& TroopOBJ)
{
    return IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && TroopOBJ.isactive && IsUnitSelected(TroopSelected, TroopOBJ);
}

std::pair<bool, Troop*> MouseCollisionWithTroop(std::vector<Troop*> TroopList, Vector2 GlobalMouse)
{
    std::pair<bool, Troop*> buffer;
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && !IsKeyDown(KEY_LEFT_SHIFT))
    {
        for (int i = 0; i < TroopList.size(); ++i)
        {
            if (CheckCollisionPointRec(GlobalMouse, TroopList[i]->hitbox))
            {
                buffer = {true, TroopList[i]};
                return buffer;
            }
        }
       
    }
    buffer = {false, NULL };
    return buffer;
}
void UpdateTroopHitbox(Rectangle& r, Vector2 m) 
{
   r.x = m.x;
   r.y = m.y;
}

