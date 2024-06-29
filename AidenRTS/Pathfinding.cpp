#include "pathfinding.h"
#include <map>
#include <chrono>
void GenerateCells(std::vector<std::vector<UltraRect>>& Grid, std::priority_queue<UltraRect*>& UR_priority, int col, int row)
{
    Vector2 placeholders = { 0,0 };
    int a = 0;
    SetRandomSeed((unsigned int)std::time(NULL));
    //since above init it doesnt set a random seed

    for (int i = 0; i < row; ++i)
    {   
        std::vector<UltraRect> rowCells;
        for (int t = 0; t < col; ++t)
        {
            rowCells.emplace_back(UltraRect::UltraRect(placeholders.x, placeholders.y));

            a = GetRandomValue(0, 20);

            if (a == 20)
            {
                rowCells[t].VisColor = BLUE;
                rowCells[t].state = 1;
            }

            placeholders.x += 11;
        }
        Grid.push_back(rowCells);
    }



   
}

void CalcH(std::vector<std::vector<UltraRect>> Grid,UltraRect* end, int col, int row)
{
    for (int i = 0; i < row; ++i)
    {
        for (int t = 0; t < col; ++t)
        {
            Grid[i][t].h_val = Vector2Distance(Grid[i][t].SelfXY, end->SelfXY);
        }
    }
}

