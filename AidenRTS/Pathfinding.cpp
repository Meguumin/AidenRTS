#include "pathfinding.h"
#include <map>
#include <chrono>
#include <cmath>
#include "buildings.h"

void CalcH(std::vector<std::vector<Node>>& Nodelist, Node* end, int row, int col)
{
    //heurteristic
    for (int i = 0; i < row; ++i)
    {
        for (int t = 0; t < col; ++t)
        {
            float dx = std::abs(Nodelist[i][t].xpos - end->xpos);
            float dy = std::abs(Nodelist[i][t].ypos - end->ypos);
               
            Nodelist[i][t].values[1] = 1 * (dx + dy) + (sqrt(2) - 1 * 1) * std::min(dx, dy);
        }
    }

}

void CalcGandF(Node* current, std::vector<Node*> adjacents)
{
    for (auto i : adjacents)
    {
        i->values[2] = i->multi;
        //F_val
        i->values[0] = i->values[1] + i->values[2];

    }
   
}
       

// Grid is 1000 x 1000
std::vector<Node*> GetAdjCells(std::vector<std::vector<Node>>& Nodelist, Node* current, int row, int col) {
    std::vector<Node*> adjacents;

    // Define offsets for movement in all eight directions
    int dx[] = { -1, 0, 1, 0, -1, -1, 1, 1 };
    int dy[] = { 0, 1, 0, -1, -1, 1, -1, 1 }; // dx and dy correspond to directions: left, right, up, down, and four diagonals

    for (int i = 0; i < 8; ++i) {
        int newX = current->index + dx[i];
        int newY = current->index2 + dy[i];

        // Check bounds and conditions
        if ((newX >= 0 && newX < row) && (newY >= 0 && newY < col) && !Nodelist[newX][newY].nodevisited && Nodelist[newX][newY].state != 1)
        {
            Nodelist[newX][newY].parent = current;
            if (i < 4) 
            { // Non-diagonal movement
                adjacents.push_back(&Nodelist[newX][newY]);
            }
            else 
            { // Diagonal movement, apply multiplier if needed
                Nodelist[newX][newY].multi = 1.4;
                adjacents.push_back(&Nodelist[newX][newY]);
            }
        }
    }

    return adjacents;
}

bool CollisionWithGameObjects(std::vector<Rectangle> GameMap, Vector2 CollisionPoint)
{
   
      for (auto rect : GameMap)
        {
        if (CheckCollisionPointRec(CollisionPoint, rect))
        {
            return false;
        }
        }
    return true;   
    
  
}

bool CollisionWithOpponentBuildings(std::vector<Building*> GameMap, Vector2 CollisionPoint, Troop* ATroop)
{

    for (auto Building : GameMap)
    {
        if (CheckCollisionPointRec(CollisionPoint, Building->hitbox))
        {
            ATroop->buildingattacktarget = Building;
            return true;
        }
    }
    return false;


}


std::pair<short, short> GetGridIndex(Vector2 Globalmouse)
{
    std::pair<short, short> index = { 0,0 };

    index.first = floor((Globalmouse.x ) / 11);
    index.second = floor((Globalmouse.y) / 11);

    return index;
}

void GenerateCells(std::vector<std::vector<Node>>& Nodelist, std::vector<Rectangle> GameMap, std::vector<Ore> CrystalMap, int row, int col)
{
    short x = 0;
    short y = 0;
    for (int i = 0; i < row; ++i)
    {
        std::vector<Node> rowCells;
        for (int t = 0; t < col; ++t)
        {
           
                rowCells.push_back(Node());
                Node& newNode = rowCells.back();

                newNode.index = i;
                newNode.index2 = t;
              
                newNode.state = 0;
            
                newNode.xpos += x;
                newNode.ypos += y;
                x += 11;

                
             
                for (auto rect : GameMap)
                {
                    if (CheckCollisionPointRec(Vector2{ float(x),float(y) }, rect))
                    {
                        newNode.state = 1; // Wall state
                    }
                }
                /*
                   for (auto ore : CrystalMap)
                {
                    if (CheckCollisionPointRec(Vector2{ float(x),float(y) }, ore.Rectangle))
                    {
                        newNode.state = 1; // Wall state
                    }
                }
                */
             
        }
        x = 0;
        y += 11;
        Nodelist.push_back(rowCells);
    }

   
}
