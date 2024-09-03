#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"
#include <algorithm> 
#include <queue>


class Building;
class Troop;
class Ore;
struct Node
{
	//H, G and F values
	bool nodevisited = false;
	//State 0 = nothing , 1 for wall, 2 for start and 3 for end
	short state = 0;
	short index = 0;
	short index2 = 0;
	short multi = 1;
	short xpos = 0;
	short ypos = 0;
	float values[3];
	Node* parent;
	// F_val = 0, H_val = 1, G_val = 2
	//Switch Statement For c
};
	
class PathfindingHandler
{
	public:
		Node* startnode;
		Node* endnode;

		std::vector<Node*> visited;
		std::vector<Node*> path;
		std::vector<Node*> Queue;

		
};

class GenericMovement : public PathfindingHandler
{
public:
	void PathINIT(Vector2 Globalmouse, std::vector<std::vector<Node>>& Nodelist, Troop& TroopOBJ);
	void FindPath(Troop& TroopOBJ, std::vector<std::vector<Node>>& Nodelist);
};

class MeleeMovement : public PathfindingHandler
{
public:
	
	void FindAttackPathForBuilding(Vector2 GlobalMouse, std::vector<std::vector<Node>>& Nodelist, Building* ABuilding, Troop &TroopOBJ);
	void FindAttackTroop(std::pair<bool, Troop*> buff, std::vector<std::vector<Node>>& Nodelist, Troop &TroopOBJ);
	//void DeathMethod(std::vector<Soldier>& GridOSoldier, std::vector<Troop*>& TotalTroops, std::vector<Troop*>& OppTotalTroops, std::vector<Soldier>& GridOppSoldier);
};


void GenerateCells(std::vector<std::vector<Node>>& Nodelist, std::vector<Rectangle> GameMap, std::vector<Ore> CrystalMap,int row, int col);
std::pair<short, short> GetGridIndex(Vector2 Globalmouse);
std::vector<Node*> GetAdjCells(std::vector<std::vector<Node>>& Nodelist, Node* current, int row, int col);
void CalcH(std::vector<std::vector<Node>>& Nodelist, Node* end, int row, int col);
bool CollisionWithGameObjects(std::vector<Rectangle> GameMap, Vector2 CollisionPoint);
bool CollisionWithOpponentBuildings(std::vector<Building*> GameMap, Vector2 CollisionPoint, Troop* ATroop);
void CalcGandF(Node* current, std::vector<Node*> adjacents);



