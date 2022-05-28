#include <stdlib.h>
#include <iostream>
#include <cstring>
using namespace std;
const int MAX_HEIGHT = 6;
const int MAX_WIDTH = 6;

bool findUncoveredGrid(int board[][MAX_WIDTH], int height, int width, int &r_id, int &c_id)
{
    // to be completed
    //
    return true;
}

int inputX, inputY, resultCal = 0;
bool boardCal[MAX_WIDTH + 1][MAX_HEIGHT + 1];
bool debugSwitch = false;

void calResult(int calX, int calY)
{
    if (calX == inputX + 1) //No more space, end function
    {
        resultCal++;
        if (debugSwitch)
        {
            cout << "if A" << endl;
            cout << "resultCal: " << resultCal << endl;
        }
        return;
    }
    if (boardCal[calX][calY] == true) //already have tile
    {
        if (debugSwitch)
        {
            cout << "if B" << endl;
        }
        if (calY == inputY) //only left 1 column, try next row
        {
            if (debugSwitch)
            {
                cout << "if C" << endl;
            }
            calResult(calX + 1, 1);
        }
        else                //only left 1 row, try next column
        {
            if (debugSwitch)
            {
                cout << "if D" << endl;
            }
            calResult(calX, calY + 1);
        }
    }
    if (boardCal[calX][calY] == false) //not have tile
    {
        if (debugSwitch)
        {
            cout << "if E" << endl;
        }
        if (calY < inputY && boardCal[calX][calY + 1] == false) //not last column and next column not tiled
        {
            boardCal[calX][calY] = true;
            boardCal[calX][calY + 1] = true;
            if (calY + 1 == inputY) //only left 1 column, try next row
            {
                if (debugSwitch)
                {
                    cout << "if F" << endl;
                }
                calResult(calX + 1, 1);
            }
            else                    // try next column(after place 2x1 tile)
            {
                if (debugSwitch)
                {
                    cout << "if G" << endl;
                }
                calResult(calX, calY + 2);
            }
            boardCal[calX][calY + 1] = false;
            boardCal[calX][calY] = false;
        }
        if (calX < inputX && boardCal[calX + 1][calY] == false) //not last column and next row not tiled
        {
            if (debugSwitch)
            {
                cout << "if H" << endl;
            }
            boardCal[calX + 1][calY] = true;
            boardCal[calX][calY] = true;
            if (calY == inputY) //only left 1 column, try next row
            {
                if (debugSwitch)
                {
                    cout << "if I" << endl;
                }
                calResult(calX + 1, 1);
            }
            else                // try next column(after place 1x2 tile)
            {
                if (debugSwitch)
                {
                    cout << "if J" << endl;
                }
                calResult(calX, calY + 1);
            }
            boardCal[calX + 1][calY] = false;
            boardCal[calX][calY] = false;
        }
    }
}

int numberLayout(int board[][MAX_WIDTH], int height, int width)
{
    inputX = width;
    inputY = height;
    calResult(1, 1);
    return resultCal;
}

int main()
{
    int width, height;
    int board[MAX_HEIGHT][MAX_WIDTH] = {};

    // enter the height (number of rows)
    do
    {
        cout << "Please enter the height [1, " << MAX_HEIGHT << "]:" << endl;
        cin >> height;
    } while ((height < 1) || (height > MAX_HEIGHT));

    // enter the width (number of columns)
    do
    {
        cout << "Please enter the width [1, " << MAX_WIDTH << "]:" << endl;
        cin >> width;
    } while ((width < 1) || (width > MAX_WIDTH));

    cout << "The number of layouts is " << numberLayout(board, height, width) << "." << endl;

    return 0;
}