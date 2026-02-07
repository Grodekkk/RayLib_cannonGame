#include "raylib.h"
#include <iostream>
#include "Ball.cpp"
#include <vector>
using namespace std;


const int screenWidth = 800;
const int screenHeight = 600;

const int positiveShift = 3;
const int negativeShift = -3;

//BORDERY FRAME'A
const int downBorder = screenHeight;
const int rightBorder = screenWidth;
const int upBorder = 0;
const int leftBorder = 0;

//initial position of the ball
int xPos = 50;
int yPos = 50;

//PRZESUNIECIA
int xShift = 3;
int yShift = 3;

//enumy kierunków
enum Level {
    RIGHTDOWN,
    RIGHTUP,
    LEFTUP,
    LEFTDOWN
};

Level currentDir = RIGHTDOWN;


void changeDirection(Level &currentDir)
{
    switch (currentDir)
    {
    case RIGHTDOWN:
        currentDir = RIGHTUP;
        xShift = positiveShift;
        yShift = negativeShift;
        /* //somehow this makes it ummmmmmmmm
        if (yPos > (screenHeight - 20))
        {
            yPos = screenHeight - 20;
        }
        */
        cout << "zmiana pozycji z RIGHTDOWN na RIGHTUP" << endl;
        break;
    case RIGHTUP:
        currentDir = LEFTUP;
        xShift = negativeShift;
        yShift = negativeShift;
        cout << "zmiana pozycji LEFTUP" << endl;
        break;
    case LEFTUP:
        currentDir = LEFTDOWN;
        xShift = negativeShift;
        yShift = positiveShift;
        cout << "zmiana pozycji LEFTDOWN" << endl;
        break;
    case LEFTDOWN:
        currentDir = RIGHTDOWN;
        xShift = positiveShift;
        yShift = positiveShift;
        cout << "zmiana pozycji RIGHTDOWN" << endl;
        break;
    }
}

void DrawCircleColor()
{
    switch (currentDir)
    {
    case RIGHTDOWN:
        DrawCircle(xPos, yPos, 10, GREEN);
        break;
    case RIGHTUP:
        DrawCircle(xPos, yPos, 10, RED);
        break;
    case LEFTUP:
        DrawCircle(xPos, yPos, 10, SKYBLUE);
        break;
    case LEFTDOWN:
        DrawCircle(xPos, yPos, 10, PINK);
        break;
    }
    
}

void updateBallPosition()
{
    xPos = xPos + xShift;
    yPos = yPos + yShift;
}

int main() {
    std::vector<Ball> balls;
    balls.emplace_back(120, 30, 15);
    balls.emplace_back(25, 50, 5);

    InitWindow(screenWidth, screenHeight, "Kocham_Mysq.EXE");
    SetTargetFPS(60);

    //main game loop
    while (!WindowShouldClose()) 
    {           
        BeginDrawing();
        ClearBackground(BLACK);
        
        for (size_t i = 0; i < balls.size(); i++)
        {
            balls[i].updateBallPosition();
            balls[i].DrawCircleColor();
            balls[i].checkForDirChange();
        }

            //drawing the circle
            updateBallPosition();
            
            DrawCircleColor();
            if (xPos <= 20 || xPos >= (screenWidth - 20) || yPos <= 20 || yPos >= (screenHeight - 20))
            {
                changeDirection(currentDir);
            }
            //cout << "current dir: " << currentDir << endl;
            
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
