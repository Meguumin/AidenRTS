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
#include "audiohandler.h"
#include <vector>
#include <stdio.h>
#include <string>

#include <map>
//look into std::map

    int main(void)
    {
        const int screenWidth = 1200;
        const int screenHeight = 1200;

        Vector2 GlobalMouse = { 0,0 };
        Camera2D Pcamera = { {500, 500}, {0, 0}, 0.0f, 2.0f };
        Rectangle Bordertangle = { 0, 0, 1000, 1000 };

       

        std::vector<UltraRect> Grid;
        // 
        //total soldiers
        std::vector<Soldier> GridOSoldier;
        std::vector<Medic> GridOMedic;

        std::vector<Troop*> TroopSelected;
        std::vector<Troop*> TotalTroops;

        std::vector<Refinery> Refineries;
        std::vector<Barrack> Barracks;
        std::vector<Building*> TotalBuildings;

        std::vector<Ore> ListOres;
      //  Ore Tempore;
      // 
        //temp fix switch both to linked list
        GridOSoldier.reserve(1000);
        GridOMedic.reserve(1000);
        //pointers get reset then 
        Refineries.reserve(1000);
        Barracks.reserve(1000);
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
        Rectangle Medicbutton = { 820, 270, 50, 50 };
        Rectangle Soldierbutton = { 875, 270, 50, 50 };

        std::vector<Rectangle*> Buttons =  { &Refinerybutton, &Barrackbutton, &Soldierbutton,&SelectionStructurebutton, &Medicbutton ,&SelectionTroopbutton };
       //button layering issue?
        enum BPlacementStates
        {
            NOTHINGSELECTED= 0,
            PLACEREFINERY,
            PLACEBARRACKS,
        }PlacementS = NOTHINGSELECTED;
 
        CommandCenter Top;

        typeofmovement movement = square;
       
        Rectangle slider_rect = { 400, 940, 350, 40 };
       
        InitWindow(screenWidth, screenHeight, "RTS Testing");
        InitAudioDevice();
       // Music Crab = LoadMusicStream("Crab.mp3");
        GenerateCells(Grid);
        // play around with different ore times and make delay while in the truck optimization and add directions, make soldiers linked lists, evaulate, crashes when multiple trucks are on ore cause it gets removed
        //Going back to 0,0? adjust ore truck to new ore system with pointers
        // optimize previos code
        //add quality of life features, also add camera speed slider
        GenerateOre(ListOres, 10000);
       // PlayMusicStream(Crab);
        while (!WindowShouldClose())
        {
    
          GlobalMouse = GetScreenToWorld2D(GetMousePosition(), Pcamera);
          UpdateCamera(Pcamera,CameraLocation,cameraspeed );
          UpdateZoom(Pcamera);
         // UpdateMusicStream(Crab);
        
             
          if (IsKeyPressed(KEY_T))
          {
             // newSoldier.location = {float(GetRandomValue(0, 100)), float(GetRandomValue(0, 100)) };
              //newSoldier.hitbox = { 0,0,15,15 };
              //GridOSoldier.push_back(newSoldier);
          }
         
              for (int i = 0; i < TotalTroops.size(); ++i)
              {
                  // Check if right mouse button is pressed or the soldier is active  
                  if (EnableTarget(*TotalTroops[i]) || TotalTroops[i]->setupmovement == false)
                  {
                      //isunit stationary not working and is unit selected
                          if (IsUnitStationary(TroopSelected, *TotalTroops[i]) || UnitRepositionCheckWhileMoving(TroopSelected, *TotalTroops[i]))
                          {
                              TotalTroops[i]->target = GetScreenToWorld2D(GetMousePosition(), Pcamera);

                          }
                      if (ShouldFollowMouse(TroopSelected, *TotalTroops[i]) || TotalTroops[i]->setupmovement == false)
                      {
                          FollowMouse(movement, *TotalTroops[i], TroopSelected);
                      }
                  }
                  UpdateTroopHitbox(TotalTroops[i]->hitbox, TotalTroops[i]->location);
                  CurrentlySelected(TroopSelected, TotalTroops, GlobalMouse, sBox, i);
                  //Selection( GlobalMouse,  sBox, GridOSoldier[i],GridOSoldier);
                  //Deselection(GlobalMouse, sBox, GridOSoldier[i], GridOSoldier);
              }
             
              for (int i = 0; i < Refineries.size(); ++i)
              {
                  Refineries[i].UpdateTrucks(Refineries[i].childtrucks,ListOres, money);   
              }

              if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
              {
                  ManageCreationOfBuilding(PlacementS, GlobalMouse, Refineries, money, Top, Barracks, TotalBuildings, Buttons);
              }

              if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !Top.CommandCenterPlaced)
              {
                  Top = Top.CreateNewCommandCenter(GlobalMouse);
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
            for (int i = 0; i < Grid.size(); ++i)
            {
                DrawRectangleRec(Grid[i].Box, Fade(GRAY, 0.2));
            }
            
            DrawRectangleRec(Bordertangle, GRAY);

     

            //DrawCircleV(Vector2{Center.x, Center.y}, 5, BLUE);
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
            {
                DrawCircleV(GlobalMouse, 10, Fade(YELLOW, 0.5));
            }
           // Drawcircleobj(troopcollider, WHITE);
            Drawbuildinghighlights(PlacementS,GlobalMouse,Top.range);
           
            if (!Top.CommandCenterPlaced)
            {
                DrawRectangleV(GlobalMouse, Vector2{ 70,70 }, Fade(GREEN, 0.3f));
            }
            else
            {
                Top.DrawCommandCenter(Top);
            }

            for (int i = 0; i < ListOres.size(); ++i)
            { 
             // DrawRectangleRec(ListOres[i].Rectangle, PURPLE);
              DrawRectanglePro(ListOres[i].Rectangle, Vector2{ListOres[i].Rectangle.width /2,ListOres[i].Rectangle.height / 2 }, ListOres[i].randomrotation, PURPLE);
              //DrawRectanglePro(ListOres[i].Rectangle, Vector2{ ListOres[i].OreLocation.x + ListOres[i].Rectangle.width / 2,ListOres[i].OreLocation.y + ListOres[i].Rectangle.height / 2 }, ListOres[i].randomrotation, PURPLE);
            }

            for (int i = 0; i < Barracks.size(); ++i)
            {
                DrawRectangleRec(Barracks[i].hitbox, BLUE);
            }
            for (int i = 0; i < TotalTroops.size(); ++i)
            {

                DrawRectangleRec(TotalTroops[i]->hitbox, TotalTroops[i]->Dcolor);
                DrawLineEx(GetCenterPositionOfRectangle(TotalTroops[i]->location, TotalTroops[i]->hitbox), CalculateEnd(TotalTroops[i]), 1, BLACK);
                //draw lines to indicate pov
               // DrawRectanglePro(GridOSoldier[i].hitbox, Vector2{GridOSoldier[i].hitbox.width /2 ,GridOSoldier[i].hitbox.height/2 }, GridOSoldier[i].rotation, WHITE);
                if (IsUnitSelected(TroopSelected,  *TotalTroops[i]))
                {
                    TotalTroops[i]->DrawHealth();
                 }
              
                if (std::find(TroopSelected.begin(), TroopSelected.end(), TotalTroops[i]) != TroopSelected.end())
                {
                    DrawRectangleLinesEx(TotalTroops[i]->hitbox, 1, GOLD);
                }
            }


            for (int i = 0; i < Refineries.size(); ++i)
            {
                DrawRectangleRec(Refineries[i].hitbox, ORANGE);
                if (Refineries[i].DT == true)
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
            EndMode2D();


         //Gui
           // DrawText(TextFormat("Cspeed: %i", cameraspeed), 0, 0, 40, WHITE);
            drawmoneytop(money);
            if (Top.CommandCenterPlaced)
            {
                DrawRectangle(810, 10, 380, 480, Fade(GRAY, 0.85f));
                DrawRectangleLines(810, 10, 380, 480, BLACK);
                if (GuiButton(SelectionStructurebutton, "Structure"))
                {
                    menu = 1;
                }
                if (GuiButton(SelectionTroopbutton, "Troops"))
                {
                    menu = 2;
                }
                switch (menu) {
                case 1:
                    if (GuiButton(Refinerybutton, "Refinery"))
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
                    if (GuiButton(Barrackbutton, "Barracks"))
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
                    break;
                case 2:
                    if (GuiButton(Soldierbutton, "Infantry"))
                    {
                        if (Barracks.size() > 0)
                        {
                            money -= 100;
                              SetupTroop(1, &Barracks[0], GridOSoldier,TotalTroops, GridOMedic);
                        }
                    }

                    if (GuiButton(Medicbutton, "Medic"))
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
        //UnloadMusicStream(Crab);   // Unload music stream buffers from RAM
       // CloseAudioDevice();
        CloseWindow();
        return 0;
    }
    