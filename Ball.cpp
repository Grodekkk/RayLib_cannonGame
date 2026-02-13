#include "raylib.h"
#include <iostream>
using namespace std;

class Ball
{
private:

    //this implementation makes ball always follow 45 degree angle
	int XpositiveShift = 3;          
    int XnegativeShift = -3;
    int YpositiveShift = 1;
    int YnegativeShift = -1;
    
    //this implementation makes ball always start with rightdown direction, setting direction setting might be used in the constructor for setting
    //TODO: how rest of program will know enum?
    int xShift = 3;
    int yShift = 3;

    //initial/current ball position
	int xPos;		
	int yPos;

    //size of the ball
	int radius;

    //current borders of the window
    int screenWidth;    
    int screenHeight;

public:
    //enumeration of directions ball follows
    enum Level 
    {
        RIGHTDOWN,
        RIGHTUP,
        LEFTUP,
        LEFTDOWN
    };

    //current direction of the ball
    Level currentDir;  //also need to be stated in the constructor

    //constructor of an object
    Ball(int x, int y, float r, int screenW, int screenH, Level dir = RIGHTDOWN)
        : xPos(x), yPos(y), radius(r), screenWidth(screenW), screenHeight(screenH), currentDir(dir)
    {
        // ustaw shift zgodnie z dir (albo zawołaj changeDirection "od zera")
        xShift = XpositiveShift;
        yShift = YpositiveShift;
    }

    //returns target direction based on movement of a ball and wall it hits.
    Level getDirectionToChange()
    {
        //case 1: ball is going DOWNRIGHT
        if (currentDir == RIGHTDOWN)
        {
            //hit bottom wall -> RIGHTUP
            if (yPos >= (screenHeight - radius))
            {
                return RIGHTUP;
            }

            //hit right wall -> LEFTDOWN
            if (xPos >= (screenWidth - radius))
            {
                return LEFTDOWN;
            }

            //error handling
            cout << "error in getDirectionToChange(), case 1:" << endl;
        }

        //case 2: ball is going RIGHTUP
        if (currentDir == RIGHTUP)
        {
            //ball hit right wall -> LEFTUP
            if (xPos >= (screenWidth - radius))
            {
                return LEFTUP;
            }

            //ball hit upper wall -> RIGHTDOWN
            if (yPos <= radius)
            {
                return RIGHTDOWN;
            }

            //error handling 
            cout << "error in getDirectionToChange(), case 2:" << endl;
            return LEFTUP;
            
        }

        //case 3: ball is going LEFTUP
        if (currentDir == LEFTUP)
        {
            //ball hit upper wall -> LEFTDOWN
            if (yPos <= radius)
            {
                return LEFTDOWN;
            }
            
            //ball hit left wall -> RIGHTUP
            if (xPos <= radius)
            {
                return RIGHTUP;
            }

            //error handling
            cout << "error in getDirectionToChange(), case 3:" << endl;
            return LEFTDOWN;
        }

        //case 4: ball is going LEFTDOWN
        if (currentDir == LEFTDOWN)
        {
            //ball hit the left wall -> RIGHTDOWN
            if (xPos <= radius)
            {
                return RIGHTDOWN;
            }

            //ball hit the bottom wall -> LEFTUP
            if (yPos >= (screenHeight - radius))
            {
                return LEFTUP;
            }

            //error handling
            cout << "error in getDirectionToChange(), case 4:" << endl;
            return RIGHTDOWN;
        }
        cout << "error in getDirectionToChange()" << endl;
        return RIGHTDOWN;
    }

    //reworked function of changing direction, direction change no longer follows "circle pattern" instead, direction is changed to the direction passed as an argument
    //possible problem: enum of direction is a part of a class. How method outside will know which change to pass?
    //TODO: another method/function to correct out of bounds/ inside obstacle problem.
    //metoda zwracająca odpowiedni direction po wykonaniu obliczen? poki co tylko na granice, skąd kulka zna granice mapy? (problem)
    //czy ta cała logika ma sens?
    void changeDirectionTo(Level targetDirection) //do we pass this correctly, relearn about pointers
    {
        switch (targetDirection)
        {
            //changes ball movement to right and down
            case RIGHTDOWN:
                    currentDir = RIGHTDOWN;
                    xShift = XpositiveShift;
                    yShift = YpositiveShift;
                    cout << "direction changed to RIGHTDOWN" << endl;
                    break;

            case RIGHTUP:
                currentDir = RIGHTUP;
                xShift = XpositiveShift;
                yShift = YnegativeShift;
                cout << "direction changed to RIGHTUP" << endl;
                break;

            case LEFTUP:
                currentDir = LEFTUP;
                xShift = XnegativeShift;
                yShift = YnegativeShift;
                cout << "direction changed to LEFTUP" << endl;
                break;

            case LEFTDOWN:
                currentDir = LEFTDOWN;
                xShift = XnegativeShift;
                yShift = YpositiveShift;
                cout << "direction changed to LEFTDOWN" << endl;
                break;
        }
    }

    //drawing circle, currently hardcoded colors for directions
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

    //
    void updateBallPosition()
    {
        xPos = xPos + xShift;
        yPos = yPos + yShift;
    }

    void checkBorders()
    {
        if (xPos <= radius || xPos >= (screenWidth - radius) || yPos <= radius || yPos >= (screenHeight - radius))
        {
            Level target = getDirectionToChange();
            changeDirectionTo(target);
        }
    }
};
