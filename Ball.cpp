#include "raylib.h"
#include <iostream>

using namespace std;

class Ball
{
private:
	int positiveShift = 3;
    int negativeShift = -3;
    int speed;
	int xPos;		//initial position stated in constructor
	int yPos;
	int radius;
    const int screenWidth = 800;
    const int screenHeight = 600;

	

    //this is straight up wrong, will make ball always go rightdown
    int xShift = 3;
    int yShift = 3;

public:
    enum Level {
        RIGHTDOWN,
        RIGHTUP,
        LEFTUP,
        LEFTDOWN
    };

    Level currentDir;  //also need to be stated in the constructor

    Ball(int x, int y, float r, Level dir = RIGHTDOWN)
        : xPos(x), yPos(y), radius(r), currentDir(dir)
    {
        // ustaw shift zgodnie z dir (albo zawołaj changeDirection "od zera")
        xShift = positiveShift;
        yShift = positiveShift;
    }

    void changeDirection()
    {
        switch (currentDir)
        {
        case RIGHTDOWN:
            currentDir = RIGHTUP;
            xShift = positiveShift;
            yShift = negativeShift;
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
            DrawCircle(xPos, yPos, radius, GREEN);
            break;
        case RIGHTUP:
            DrawCircle(xPos, yPos, radius, RED);
            break;
        case LEFTUP:
            DrawCircle(xPos, yPos, radius, SKYBLUE);
            break;
        case LEFTDOWN:
            DrawCircle(xPos, yPos, radius, PINK);
            break;
        }

    }

    void updateBallPosition()
    {
        xPos = xPos + xShift;
        yPos = yPos + yShift;
    }

    void checkForDirChange()
    {
        if (xPos <= 20 || xPos >= (screenWidth - 20) || yPos <= 20 || yPos >= (screenHeight - 20))
        {
            changeDirection();
        }
    }
};
