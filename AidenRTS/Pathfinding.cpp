#include "pathfinding.h"

void GenerateCells(std::vector<UltraRect>& Grid)
{
    Vector2 placeholders = { 0,0 };

    for (int i = 0; i < 100000; i++) {
        Grid.emplace_back(UltraRect::UltraRect(placeholders.x, placeholders.y));
        placeholders.x += 11;

        if (placeholders.x >= 5000)
        {
            placeholders.x = 0;

            placeholders.y += 11;
        }
    }
}

