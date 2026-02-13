#include "raylib.h"
#include <iostream>
#include "Ball.cpp"
#include <vector>
using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                       NOTES                                                                             //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
(1) theoretical borders for the ball:
    x:  x<radius, x>width-radius
    y:  y<radius, y>height-radius




*/



const int screenWidth = 800;
const int screenHeight = 600;

int main() {
    vector<Ball> balls;
    balls.emplace_back(120, 30, 10, screenWidth, screenHeight);
    balls.emplace_back(150, 30, 20, screenWidth, screenHeight);
    balls.emplace_back(120, 200, 5, screenWidth, screenHeight);
    balls.emplace_back(250, 90, 30, screenWidth, screenHeight);
    balls.emplace_back(400, 30, 15, screenWidth, screenHeight);
    balls.emplace_back(300, 30, 15, screenWidth, screenHeight);
    //balls.emplace_back(25, 50, 5);

    InitWindow(screenWidth, screenHeight, "Kocham_Mysq.EXE");
    SetTargetFPS(60);

    //main game loop
    while (!WindowShouldClose()) 
    {           
        BeginDrawing();
        ClearBackground(BLACK);

        //bounds testing
        //DrawCircle(400, 30, 30, GREEN);
        
        
        for (size_t i = 0; i < balls.size(); i++)
        {
            balls[i].updateBallPosition(); //shifts xy 
            balls[i].DrawCircleColor();    //drawing procedure
            balls[i].checkBorders();
        }

            
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
