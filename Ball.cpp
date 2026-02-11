#include "raylib.h"
#include <iostream>

using namespace std;

class Ball
{
private:
	int positiveShift = 3;          //this way it will be always 45 degrees
    int negativeShift = -3;
    //this is straight up wrong, will make ball always go rightdown <is it?>
    int xShift = 3;
    int yShift = 3;


	int xPos;		//initial position stated in constructor
	int yPos;
	int radius;
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
    Ball(int x, int y, float r, int screenW, int screenH, Level dir = RIGHTUP)
        : xPos(x), yPos(y), radius(r), screenWidth(screenW), screenHeight(screenH), currentDir(dir)
    {
        // ustaw shift zgodnie z dir (albo zawołaj changeDirection "od zera")
        xShift = positiveShift;
        yShift = positiveShift;
    }

    //classic change direction function, works like "cyclic circle (RD->RU->LU->LD->RD->...)"
    void changeDirection()
    {
        switch (currentDir)
        {
        case RIGHTDOWN:
            if (yPos >= screenHeight - ((radius * 3) + 5) )
            {
                currentDir = RIGHTUP;
                xShift = positiveShift;
                yShift = negativeShift;
                cout << "[N] zmiana pozycji z RIGHTDOWN na RIGHTUP" << endl;
                break;
            }
            else //kulka uderza w prawa scianke
            {
                currentDir = LEFTDOWN;
                xShift = negativeShift;
                yShift = positiveShift;
                cout << " [N] zmiana pozycji LEFTDOWN" << endl;
                break;
            }
            
        case RIGHTUP:
            currentDir = LEFTUP;
            xShift = negativeShift;
            yShift = negativeShift;
            cout << "zmiana pozycji LEFTUP" << endl;
            break;
        case LEFTUP:
            if (yPos < (radius * 4))
            {
                currentDir = LEFTDOWN;
                xShift = negativeShift;
                yShift = positiveShift;
                cout << "zmiana pozycji LEFTDOWN" << endl;
                break;
            }
            else
            {
                currentDir = RIGHTUP;
                xShift = positiveShift;
                yShift = positiveShift;
                cout << "zmiana pozycji LEFTDOWN" << endl;
                break;
            }
            
        case LEFTDOWN:
            currentDir = RIGHTDOWN;
            xShift = positiveShift;
            yShift = positiveShift;
            cout << "zmiana pozycji RIGHTDOWN" << endl;
            break;
        }
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
                    xShift = positiveShift;
                    yShift = positiveShift;
                    cout << "direction changed to RIGHTDOWN" << endl;
                    break;

            case RIGHTUP:
                currentDir = RIGHTUP;
                xShift = positiveShift;
                yShift = negativeShift;
                cout << "direction changed to RIGHTUP" << endl;
                break;

            case LEFTUP:
                currentDir = LEFTUP;
                xShift = negativeShift;
                yShift = negativeShift;
                cout << "direction changed to LEFTUP" << endl;
                break;

            case LEFTDOWN:
                currentDir = LEFTDOWN;
                xShift = negativeShift;
                yShift = positiveShift;
                cout << "direction changed to LEFTDOWN" << endl;
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

    //ball itself checks for the out of bounds state, returns true or false <or direction to change> <correcting wrong coordinates> <struct>
    bool isBallOutOfBounds()
    {

    }
};
