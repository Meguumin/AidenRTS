#include "orebehaviour.h"
#include "misc.h"
#include "troops.h"
void GenerateOre(std::vector<Ore>& ListOres, int amount)
{
	int givenid = 0;
	for (int i = 0; i < amount; ++i)
	{
		Ore newOre;
      
        switch (newOre.type) {
        case 1:
			newOre.minetime = 10;
			newOre.orehealth = 10;
            break;
        case 2:
            
            break;
       
        }
		newOre.randomrotation = float(GetRandomValue(0, 360));
		newOre.OreLocation = RandomVector2Location(-10000, 10000);
		UpdateTroopHitbox(newOre.Rectangle, newOre.OreLocation);
		newOre.ido = givenid;
		givenid++;	
		ListOres.push_back(newOre);
	}
		
}
