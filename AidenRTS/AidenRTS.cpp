#pragma once
#define RAYGUI_IMPLEMENTATION
#include <iostream>
#include "raygui.h"
#include "raymath.h"
#include "camera.h"
#include "pathfinding.h"
#include "troopselection.h"
#include "troops.h"
#include "buildings.h"
#include "orebehaviour.h"
#include "misc.h"
#include "drawgui.h"
#include "deathhandler.h"
#include "opponentbehaviour.h"
#include <queue>
#include <vector>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <algorithm> // std::min_element
#include <iterator> 

//look into std::map



    int main(void)
    {
        const int screenWidth = 1200;
        const int screenHeight = 1200;

        Vector2 GlobalMouse = { 0,0 };
        Camera2D Pcamera = { {500, 500}, {0, 0}, 0.0f, 2.0f };
        Rectangle Bordertangle = { 0, 0, 1000, 1000 };
    
           

        // 
        //total soldiers
        std::vector<std::vector<Node>> Nodelist;

        std::vector<Soldier> GridOSoldier;
        std::vector<Medic> GridOMedic;





        
        //std::vector<Medic> GridOMedic;

        std::vector<Rectangle> GameMap;
        GameMap.push_back(Rectangle{ 1000, 1000, 1000, 5000 });
        GameMap.push_back(Rectangle{ 1500, 200, 200, 100 });

        

        std::vector<Troop*> TroopSelected;
        std::vector<Troop*> TotalTroops;
        std::vector<Refinery> Refineries;
        std::vector<Barrack> Barracks;
        std::vector<PowerPlant> PowerPlants;
        std::vector<Building*> FriendlyBuildings;
        std::vector<Building*> TotalBuildings;
        std::vector<Rectangle*> RectangleBuildings;
        std::vector<Ore> ListOres;

      //  Ore Tempore;
      // 
        //temp fix switch both to linked list
        GridOSoldier.reserve(1000);
        Nodelist.reserve(1000000);
        GridOMedic.reserve(1000);
        Refineries.reserve(1000);
        Barracks.reserve(1000);
        PowerPlants.reserve(1000);
        FriendlyBuildings.reserve(1000);

        Opponent YourNightmare;
        YourNightmare.OppTotalTroops.reserve(1000);
        YourNightmare.OppRefineries.reserve(1000);
        YourNightmare.OppBarracks.reserve(1000);
        YourNightmare.OppTotalBuildings.reserve(1000);
        YourNightmare.GridOppSoldier.reserve(1000);
        enum BPlacementStates
        {
            NOTHINGSELECTED = 0,
            PLACEREFINERY = 1,
            PLACEBARRACKS = 2,
            PLACEPOWERPLANT = 3,
        }PlacementS = NOTHINGSELECTED;


        bool initial = false;   
        Pcamera.zoom = 1.0f;
        Vector2 CameraLocation = { 0, 0 };
        float cameraspeed = 1000.0f;
      
        Vector2 selectionstart = { 400, 400 };
        Vector2 selectionend = { 10, 150 };
        Rectangle sBox = {0};
        //selection box
       // Circle troopcollider;
        
        Troop newTroop;
        Building* selectedbuilding = NULL;
        int money = 10000000;
        int menu = 1;

        Rectangle SelectionStructurebutton = { 820, 240, 70, 20 };
        Rectangle SelectionTroopbutton = { 900, 240, 70, 20 };
        Rectangle Refinerybutton = { 820, 270, 50, 50 };
        Rectangle Barrackbutton = { 875, 270, 50, 50 };
        Rectangle PowerPlantbutton = { 930, 270, 50, 50 };
        Rectangle Medicbutton = { 820, 270, 50, 50 };
        Rectangle Soldierbutton = { 875, 270, 50, 50 };

        std::vector<Rectangle*> Buttons =  { &Refinerybutton, &Barrackbutton, &Soldierbutton,&SelectionStructurebutton, &Medicbutton ,&SelectionTroopbutton,&PowerPlantbutton };
       //button layering issue?


       
       


        int row = 1000;
        int col = 1000;
      
        CommandCenter Top;
        
        typeofmovement movement = square;
       
        Rectangle slider_rect = { 400, 940, 350, 40 };
       
        InitWindow(screenWidth, screenHeight, "RTS Testing");
        InitAudioDevice();
        Texture2D PowerPlanttexture = LoadTexture("resources/Powerplant.png");
        Texture2D Barracktexture = LoadTexture("resources\\Barrack.png");
        Texture2D Barrackopptexture = LoadTexture("resources/BarrackOpp.png");
        Texture2D Commandtexture = LoadTexture("resources/CommandCenter.png");
        Texture2D Commandopptexture = LoadTexture("resources/CommandCenterOpp.png");
       //Pathfinding and optimization after
        GenerateOre(ListOres, 5000, GameMap);
        GenerateCells(Nodelist,GameMap ,ListOres ,1000, 1000);
       
        
        
        YourNightmare.initializeopp(&Commandopptexture);
        YourNightmare.CreateOppBarracks(&Barrackopptexture, TotalBuildings);
        YourNightmare.CreateSoldier();

        TotalBuildings.push_back(&YourNightmare.base);
        Top.main = &Commandtexture;
        TotalBuildings.push_back(&Top);
        FriendlyBuildings.push_back(&Top);

        Music Devotion = LoadMusicStream("resources/Devotion.wav");
        PlayMusicStream(Devotion);


        std::pair<bool, Troop*> pairbuffer;

        
        while (!WindowShouldClose())
        {
          
          GlobalMouse = GetScreenToWorld2D(GetMousePosition(), Pcamera);
          UpdateCamera(Pcamera,CameraLocation,cameraspeed );
          UpdateZoom(Pcamera);
          //UpdateMusicStream(Devotion);

          int u = floor((GlobalMouse.x) / 11);
          int y = floor((GlobalMouse.y) / 11);

          if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
          {
              if (CollisionWithGameObjects(GameMap, GlobalMouse))
              {
                  for (int i = 0; i < TroopSelected.size(); ++i)
                  {
                      TroopSelected[i]->formationposition = i;
                      TroopSelected[i]->groupsize = TroopSelected.size();
                  }

              }
          }


          for (int i = 0; i < GridOSoldier.size(); i++)
          {
             
              if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && IsUnitSelected(TroopSelected, GridOSoldier[i]) && u > 0 && y > 0 && !CheckCollsionMousewithFriendlyBuildings(GlobalMouse, FriendlyBuildings))
              {
                  pairbuffer = MouseCollisionWithTroop(YourNightmare.OppTotalTroops, GlobalMouse);
                  GridOSoldier[i].AHOBJ->ResetAttack();

                  if (CollisionWithGameObjects(GameMap, GlobalMouse))
                  {
                      if (CollisionWithOpponentBuildings(YourNightmare.OppTotalBuildings, GlobalMouse, &GridOSoldier[i]))
                      {
                          GridOSoldier[i].MMOBJ.FindAttackPathForBuilding(GlobalMouse, Nodelist, TotalTroops[i]->AHOBJ->buildingattacktarget, GridOSoldier[i]);
                      }

                      //paint buffer first is a bool value to determine if mouse is on an enemy troop

                      else if (pairbuffer.first)
                      {
                         
                          GridOSoldier[i].AHOBJ->troopattacktarget = pairbuffer.second;
                          GridOSoldier[i].MMOBJ.FindAttackTroop(pairbuffer, Nodelist, GridOSoldier[i]); // Directly calls Soldier::FindAttackTroop
      
                      }
                      else {
                          GridOSoldier[i].PHOBJ.PathINIT(GlobalMouse, Nodelist, GridOSoldier[i]);
                      }
                  }
              }
              
              if (GridOSoldier[i].AHOBJ->troopattacktarget != NULL)
              {
                  if (GridOSoldier[i].AHOBJ->troopattacktarget->health <= 0)
                  {
                      // GridOSoldier[i].AHOBJ->troopattacktarget->DHOBJ->Death(GridOSoldier[i]);
                   
                  }
              }
              
              
              
          }
              for (int i = 0; i < TotalTroops.size(); ++i)
              { 
                 //TotalTroops[i]->ExitAnimation();
                
                  if (TotalTroops[i]->isactive)
                  {
                      TotalTroops[i]->NormalizeDir();
                  }
                    
                  if(TotalTroops[i]->isactive && TotalTroops[i]->PHOBJ.path.size() > 0)
                  {
                     FollowMouse(movement, *TotalTroops[i], TroopSelected, Nodelist);
                  }

                  if (TotalTroops[i]->AHOBJ->isattacking)
                  {
                      switch (TotalTroops[i]->GetAttackType())
                      {
                      case 0:

                      case 1:
                          //building attack target
                          TotalTroops[i]->AHOBJ->AttackBuilding();
                          break;
                      case 2:
                          //troop attack target
                          TotalTroops[i]->AHOBJ->AttackTroop();
                          break;
                      }
                     
                  }
                 
                  UpdateTroopHitbox(TotalTroops[i]->hitbox, TotalTroops[i]->location);
                  CurrentlySelected(TroopSelected, TotalTroops, GlobalMouse, sBox, i);
              }

          


              for (int i = 0; i < Refineries.size(); ++i)
              {
                  Refineries[i].UpdateTrucks(Refineries[i].childtrucks,ListOres, money, Nodelist);   
              }

              if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && u > 0 && y > 0)
              {
                  ManageCreationOfBuilding(PlacementS, GlobalMouse, Refineries, money, Top, Barracks, TotalBuildings, Buttons, Barracktexture, FriendlyBuildings, PowerPlants, PowerPlanttexture);
     
                  for (int i = 0; i < TotalBuildings.size(); ++i)
                  {
                      TotalBuildings[i]->SetNodes(Nodelist);
                  }
              }

            

              //Top.placeCC(GlobalMouse);
              if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !Top.CommandCenterPlaced)
              {
                  Top.initializeCC(GlobalMouse, Top.main);

              }
              for (int i = 0; i < ListOres.size(); ++i)
              {
                  ListOres[i].randomrotation += 0.01f ;
              }

              if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && PlacementS != 0)
              {
                  PlacementS = NOTHINGSELECTED;
                  
              }

              if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && selectedbuilding != NULL)
              {
                  selectedbuilding = NULL;
              }
              
              for (int i = 0; i < TotalBuildings.size(); ++i)
              {
                  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GlobalMouse, TotalBuildings[i]->hitbox) && PlacementS == 0)
                  {
                      selectedbuilding = TotalBuildings[i];
                  }
              }



            BeginDrawing();
            
            ClearBackground(BLACK);
            BeginMode2D(Pcamera);
            //DrawRectangleRec(Bordertangle, GRAY);
            //DrawSmaller
           
            
              for (auto rect : GameMap)
                {
                DrawRectangleRec(rect, GRAY);
                }
             /*
              for (int i = 0; i <Nodelist.size(); ++i)
              {
                  for (int t = 0; t < Nodelist[i].size(); ++t)
                  {
                      if (Nodelist[i][t].state == 0)
                      {
                          DrawRectangle(Nodelist[i][t].xpos, Nodelist[i][t].ypos, 10, 10, GRAY);
                      }
                      if (Nodelist[i][t].state == 1)
                      {
                          DrawRectangle(Nodelist[i][t].xpos, Nodelist[i][t].ypos, 10, 10, GREEN);
                      }


                  }

              }
             
             */
            
             
             

       

            DrawSelectionCirlce(GlobalMouse);
            Drawbuildinghighlights(PlacementS ,GlobalMouse,Top.range);
           // DrawFPS(0,0);
            if (!Top.CommandCenterPlaced)
            {
                DrawRectangleV(GlobalMouse, Vector2{ 70,70 }, Fade(GREEN, 0.3f));
            }
            else
            {
                Top.BROBJ.DrawCommandCenter(Top);
            }

            YourNightmare.base.BROBJ.DrawCommandCenter(YourNightmare.base);

            for (int i = 0; i < ListOres.size(); ++i)
            { 
             // DrawRectangleRec(ListOres[i].Rectangle, PURPLE);
              DrawRectanglePro(ListOres[i].Rectangle, Vector2{ListOres[i].Rectangle.width /2,ListOres[i].Rectangle.height / 2 }, ListOres[i].randomrotation, PURPLE);
              //DrawRectanglePro(ListOres[i].Rectangle, Vector2{ ListOres[i].OreLocation.x + ListOres[i].Rectangle.width / 2,ListOres[i].OreLocation.y + ListOres[i].Rectangle.height / 2 }, ListOres[i].randomrotation, PURPLE);
            }

            for (int i = 0; i < Barracks.size(); ++i)
            {               
                Barracks[i].BROBJ.DrawBTexture(Barracks[i]);
            }
            for (int i = 0; i < PowerPlants.size(); ++i)
            {
                PowerPlants[i].BROBJ.DrawBTexture(PowerPlants[i]);
            }

            for (int i = 0; i < YourNightmare.OppBarracks.size(); ++i)
            {
                YourNightmare.OppBarracks[i].BROBJ.DrawBTexture(YourNightmare.OppBarracks[i]);
            }

            for (auto i : TotalBuildings)
            {
                i->CalculateHealthBoxWidth();
                i->BROBJ.DrawHealth(*i);
     
            }

            for (int i = 0; i < TotalTroops.size(); ++i)
            {

                DrawRectangleRec(TotalTroops[i]->hitbox, TotalTroops[i]->Dcolor);
                
                //make most of these functions
                TotalTroops[i]->TROBJ.UpdateCircleValue(*TotalTroops[i]);

                DrawCircle(TotalTroops[i]->location.x, TotalTroops[i]->location.y, TotalTroops[i]->AHOBJ->acr, Fade(YELLOW, 0.5));
                if (IsUnitSelected(TroopSelected,  *TotalTroops[i]))
                {
                    TotalTroops[i]->TROBJ.DrawHealth(*TotalTroops[i]);
                }
              
                if (std::find(TroopSelected.begin(), TroopSelected.end(), TotalTroops[i]) != TroopSelected.end())
                {
                    DrawRectangleLinesEx(TotalTroops[i]->hitbox, 1, GOLD);
                }



                DrawLineEx(GetCenterPositionOfRectangle(TotalTroops[i]->location, TotalTroops[i]->hitbox), CalculateEnd(TotalTroops[i]), 1, BLACK);
            }


            for (int i = 0; i < YourNightmare.OppTotalTroops.size(); ++i)
            {
                DrawRectangleRec(YourNightmare.OppTotalTroops[i]->hitbox, YourNightmare.OppTotalTroops[i]->Dcolor);
                if (YourNightmare.OppTotalTroops[i]->health < YourNightmare.OppTotalTroops[i]->maxhealth)
                {
           
                    YourNightmare.OppTotalTroops[i]->TROBJ.DrawHealth(*YourNightmare.OppTotalTroops[i]);
                }      
            }


            if (TroopSelected.size() > 0)
            {
                for (int i = 0; i < TroopSelected.size(); ++i)
                {
                    TroopSelected[i]->TROBJ.DrawHealth(*TroopSelected[i]);
                }

            }

            for (int i = 0; i < Refineries.size(); ++i)
            {
                DrawRectangleRec(Refineries[i].hitbox, ORANGE);
                if (Refineries[i].MoneyAnimCheck == true)
                {
                    DrawText("+1$", int(Refineries[i].location.x - 10), int(Refineries[i].location.y - 10), 10, Fade(GREEN, float(0.2)));
                }


                for (int j = 0; j < Refineries[i].childtrucks.size(); ++j)
                {
                  
                   DrawRectangleRec(Refineries[i].childtrucks[j].hitbox, Refineries[i].childtrucks[j].Dcolor);
                   DrawLineEx(GetCenterPositionOfRectangle(Refineries[i].childtrucks[j].location, Refineries[i].childtrucks[j].hitbox), Vector2{ Refineries[i].childtrucks[j].location.x + Refineries[i].childtrucks[j].hitbox.width / 2 + Refineries[i].childtrucks[j].direction.x * 10, Refineries[i].childtrucks[j].location.y + Refineries[i].childtrucks[j].hitbox.height / 2 + Refineries[i].childtrucks[j].direction.y* 10 }, 1, BLACK);
                }
            }

      
            if (selectedbuilding != NULL)
            {
                DrawRectangleLinesEx(GetRectFromPointer(selectedbuilding), 2, GOLD);
            }

            DrawRectangleLinesEx(DrawSelection(selectionstart, selectionend, sBox, initial, Pcamera), 5, WHITE);
            DrawRectangleLinesEx(Rectangle{ -10,-10, 11000,11000 }, 10, WHITE);
            DrawRectangleLinesEx(Rectangle{0,0, 11000,11000 }, 1, WHITE);

            EndMode2D();


         //Gui
           DrawText(TextFormat(" %i", u), 0, 0, 40, WHITE);
           DrawText(TextFormat(" %i", y), 60, 0, 40, WHITE);
      
          
            drawmoneytop(money);
            if (Top.CommandCenterPlaced)
            {
               
                DrawRectangle(810, 10, 380, 480, Fade(GRAY, 0.85f));
                DrawRectangleLines(810, 10, 380, 480, BLACK);

                if (GuiButton(*Buttons[3], "Structure"))
                {
                    menu = 1;
                }

                if (GuiButton(*Buttons[5], "Troops"))
                {
                    menu = 2;
                }

                switch (menu) {
                case 1:
                    if (GuiButton(*Buttons[0], "Refinery"))
                    {
                        if (PlacementS == 0 || PlacementS == 2)//idle
                        {
                            PlacementS = PLACEREFINERY;
                        }
                        else
                        {
                            PlacementS = NOTHINGSELECTED;
                        }
                    }
                    if (GuiButton(*Buttons[1], "Barracks"))
                    {
                        if (PlacementS == 0 || PlacementS == 1)//idle
                        {
                            PlacementS = PLACEBARRACKS;
                        }
                        else
                        {
                            PlacementS = NOTHINGSELECTED;
                        }
                    }

                    if (GuiButton(*Buttons[6], "PowerGen"))
                    {
                        if (PlacementS == 0 || PlacementS == 1)//idle
                        {
                            PlacementS = PLACEPOWERPLANT;
                        }
                        else
                        {
                            PlacementS = NOTHINGSELECTED;
                        }
                    }
                    break;
                case 2:
                    if (GuiButton(*Buttons[2], "Infantry"))
                    {
                        if (Barracks.size() > 0)
                        {
                            money -= 100;
                            SetupTroop(1, &Barracks[0], GridOSoldier, TotalTroops, GridOMedic);

                        }
                    }

                    if (GuiButton(*Buttons[4], "Medic"))
                    {
                        if (Barracks.size() > 0)
                        {
                            money -= 100;
                            SetupTroop(2, &Barracks[0], GridOSoldier, TotalTroops, GridOMedic);
                        }
                    }
                    break;
                }
               

                if (selectedbuilding != NULL)
                {
                   // selectedbuilding->DrawGUI();
                }
               // DrawRectangleLines(10, 740, 980, 250, BLACK);
                //sliderbar
               // GuiSlider(slider_rect, NULL, NULL, &cameraspeed, 0.0f, 1000.0f);
            }
            
            EndDrawing();
        }
        //for loop over to unit
        UnloadMusicStream(Devotion);  
        UnloadTexture(Barracktexture);
        UnloadTexture(Barrackopptexture);
        UnloadTexture(Commandopptexture);
        UnloadTexture(Commandtexture);
        UnloadTexture(PowerPlanttexture);
        CloseAudioDevice();
        CloseWindow();
        return 0;
    }
    
    
    
    