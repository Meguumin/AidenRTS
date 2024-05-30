#pragma once
#define RAYGUI_IMPLEMENTATION
#include <iostream>
#include "raygui.h"
#include "raymath.h"
#include "Camera.h"
#include "Pathfinding.h"
#include "troopselection.h"
#include "troops.h"
#include <vector>
#include <stdio.h>
#include <string>


    int main(void)
    {
        const int screenWidth = 1000;
        const int screenHeight = 1000;

        Vector2 GlobalMouse = { 0,0 };
        Camera2D Pcamera = { {500, 500}, {0, 0}, 0.0f, 2.0f };
        Rectangle Bordertangle = { 0, 0, 1000, 1000 };

       

        //std::vector<UltraRect> Grid;
        // 
        //total soldiers
        std::vector<Soldier> GridOSoldier;

        auto SoldierSelected = CurrentlySelected(GridOSoldier);
        bool initial = false;   

        Pcamera.zoom = 1.0f;
        Vector2 CameraLocation = { 0, 0 };
       
        Vector2 selectionstart = { 400, 400 };
        Vector2 selectionend = { 10, 150 };
        Rectangle sBox = {0};
        //selection box
       // Circle troopcollider;
        Soldier NewSoldier;
        GridOSoldier.push_back(NewSoldier);
        typeofmovement movement = square;
        InitWindow(screenWidth, screenHeight, "RTS Testing");
       
        SetTargetFPS(60);
        //GenerateCells(Grid);
        //When i move around 2 groups around too much ends up glitching, cleanup code so it doesnt re iterate 2 times and add ore truck
        
        while (!WindowShouldClose())
        {
    
          GlobalMouse = GetScreenToWorld2D(GetMousePosition(), Pcamera);
          UpdateCamera(Pcamera,CameraLocation );
          UpdateZoom(Pcamera);
         
             
          if (IsKeyPressed(KEY_T))
          {
              NewSoldier.location = {float(GetRandomValue(0, 100)), float(GetRandomValue(0, 100)) };
              GridOSoldier.push_back(NewSoldier);
          }
        
         
              for (int i = 0; i < GridOSoldier.size(); ++i)
              {
                  if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || GridOSoldier[i].isactive)
                  {
                      if (GridOSoldier[i].isselected && !GridOSoldier[i].isactive || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && GridOSoldier[i].isactive && GridOSoldier[i].isselected)
                      {
                          GridOSoldier[i].target = GetScreenToWorld2D(GetMousePosition(), Pcamera);
                          
                      }
                      if (GridOSoldier[i].isselected || !GridOSoldier[i].isselected && GridOSoldier[i].isactive)
                      {
                          FollowMouse(movement, GridOSoldier[i], GridOSoldier, SoldierSelected);
                      }
                  }

                  SoldierSelected = CurrentlySelected(GridOSoldier);
                  UpdateTroopHitbox(GridOSoldier[i].hitbox, GridOSoldier[i].location);
                  Selection( GlobalMouse,  sBox, GridOSoldier[i],GridOSoldier);
                  Deselection(GlobalMouse, sBox, GridOSoldier[i], GridOSoldier);
              }
                
     
    

            BeginDrawing();
            
            ClearBackground(BLACK);
            BeginMode2D(Pcamera);

            DrawRectangleRec(Bordertangle, GRAY);

            for (int i = 0; i < GridOSoldier.size(); ++i)
            {
                DrawRectangleRec(GridOSoldier[i].hitbox, WHITE);
            }
            for (int i = 0; i < SoldierSelected.size(); ++i)
            {
                DrawRectangleLinesEx(SoldierSelected[i]->hitbox,2,GOLD);
            }

            //DrawCircleV(Vector2{Center.x, Center.y}, 5, BLUE);
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
            {
                DrawCircleV(GlobalMouse, 10, Fade(YELLOW, 0.5));
            }
           // Drawcircleobj(troopcollider, WHITE);
            DrawRectangleLinesEx(DrawSelection(selectionstart, selectionend, sBox, initial, Pcamera), 5, WHITE);
            EndMode2D();
        
            
           
            EndDrawing();
        }
        CloseWindow();
        return 0;
    }