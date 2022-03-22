#include <iostream>
using namespace std;
// you are NOT allowed to include any additional library
const int ARRAY_MAX_SIZE = 12;

// given; do NOT modify; please refer to the webpage description
void printArray(int array[], int arraySize, int currentPosition)
{
    cout << array[currentPosition];
    if (currentPosition < arraySize - 1)
    {
        if (array[currentPosition + 1] > 0)
            cout << "+";
        printArray(array, arraySize, currentPosition + 1);
    }
    else
        cout << endl;
}

// given; do NOT modify; please refer to the webpage description
void printArray(int array[], int arraySize)
{
    printArray(array, arraySize, 0);
}

//***** Only write your code below this line, remember that NO loop is allowed! *****
int arraySum(int array[], int arraySize)
{
    if (arraySize <= 0)
        return 0;
    return (arraySum(array, arraySize - 1) + array[arraySize - 1]);
    // change this line if you want
}

bool solve(int input[], int size, int target, int result[], int &resultSize)
{
    return false; // change this line if you want
}

void printString(const char str[])
{
    if (*str == '\0')
    {
        cout << '\n';
        return;
    }
    else
    {
        cout << *str;
        printString(str + 1);
    }
}
float pow(float x, int y)
{
    float temp;
    if (y == 0)
        return 1;
    temp = pow(x, y / 2);
    if (y % 2 == 0)
        return temp * temp;
    else
    {
        if (y > 0)
            return x * temp * temp;
        else
            return (temp * temp) / x;
    }
}

int getIntValue(const char str[], int start, int end)
{
    if ((end - start) <= 0)
        return str[start] - 48;
    return (getIntValue(str, start + 1, end) + (str[start] - 48) * (pow(10, end - start)));
}

int strlen(const char str[])
{
    if (*str == 0)
    {
        return 0;
    }
    return strlen(str + 1) + 1;
}
int findNext(const char str[], int lens, int start)
{
    if (start >= lens)
    {
        return -1;
    }
    if (str[start] >= '0' && str[start] <= '9')
    {
        return findNext(str, lens, start + 1);
    }
    else
    {
        // cout << str[start] << ":"<<start << endl ;
        return start;
    }
}

int findBack(const char str[], int lens, int start)
{
    if (start < 0)
    {
        return -1;
    }
    if (str[start] >= '0' && str[start] <= '9')
    {
        return findBack(str, lens, start - 1);
    }
    else
    {
        // cout << str[start] << ":"<<start << endl ;
        return start;
    }
}

int evaluate(const char str[], int start, int end, int lens)
{
    if (end - start < 0)
    {
        return 0;
    }

    int next = findNext(str, lens, start);
    //cout << "Begin: " << start << " end: " << end << " next: " << next << endl;
    if (next == -1)
    {
        if(str[findBack(str,lens,start)]== '-'){
            return -getIntValue(str, start, end);
        }
        return getIntValue(str, start, end);
    }
    else if (next != start)
    {

        //cout << "IF | start: " << start << " end: " << end << " next: " << next << endl;
        //cout << "get Value: " << getIntValue(str, start, next - 1)<<endl;
        if(str[findBack(str,lens,start)]== '-'){
            return evaluate(str, start + (next-start+1) , end, lens) - getIntValue(str, start, next - 1);
        }
        return evaluate(str, start + (next-start+1) , end, lens) + getIntValue(str, start, next - 1);
    }
    else if (next == 0)
    {
        int next2 = findNext(str, lens, next + 1);
        int temp2;

        if (next2 != -1)
        {
            temp2 = next2;
            //cout << "temp2:" << temp2 << endl;
        }
        else
        {
            temp2 = end;
        }

        if (str[next] == '+')
        {
            //cout << "IF Add 2| start: " << start << " temp2: " << temp2 << " next: " << next << endl;
            return evaluate(str, temp2 + 1, end, lens);
        }
        else if (str[next] == '-')
        {
            //cout << "IF Sub 2| start: " << start << " temp2: " << temp2 << " next: " << next << endl;
            
            return evaluate(str, temp2 + 1, end, lens) - getIntValue(str, next + 1, temp2);
        }
    }
}

int evaluate(const char str[])
{
    int lens = strlen(str);
    return evaluate(str, 0, lens - 1, lens);
}

//***** Only write your code above this line, remember that NO loop is allowed! *****

int main()
{
    int testCase;
    cout << "Hi, recursion master! Which test case do you want to run?" << endl;
    cin >> testCase;

    cout << endl
         << "Test case " << testCase << " output:" << endl;
    cout << "===================================" << endl;

    if (testCase == 0) // this test case is used to show you how printArray works; it is NOT used to grade your work and it is NOT on ZINC; no mark is allocated to this; try it on your own computer if you want
    {
        int array1[] = {1, 2, 3};
        printArray(array1, 3);
        int array2[] = {1, 2, 3, -4};
        printArray(array2, 4);
        int array3[] = {-8, 2, 1, -4};
        printArray(array3, 4);
        int array4[] = {99};
        printArray(array4, 1);
        int array5[] = {-1199};
        printArray(array5, 1);
    }

    else if (testCase == 1) // test arraySum
    {
        int array[] = {1, 2, 3};
        cout << arraySum(array, 3) << endl;
    }
    else if (testCase == 2) // test arraySum
    {
        int array[] = {-1, -234, 33, 5};
        cout << arraySum(array, 4) << endl;
    }

    else if (testCase == 3) // test solve
    {
        int input[] = {1, 2, 3, 4};
        int size = 4;
        int target = 2;
        int result[ARRAY_MAX_SIZE] = {}; // filled with '\0'
        int resultSize = 0;
        if (solve(input, size, target, result, resultSize))
        {
            cout << "solved: ";
            printArray(result, resultSize);
        }
        else
            cout << "no solution!" << endl;
    }
    else if (testCase == 4) // test solve
    {
        int input[] = {1, 2, 3, 4};
        int size = 4;
        int target = -2;
        int result[ARRAY_MAX_SIZE] = {}; // filled with '\0'
        int resultSize = 0;
        if (solve(input, size, target, result, resultSize))
        {
            cout << "solved: ";
            printArray(result, resultSize);
        }
        else
            cout << "no solution!" << endl;
    }
    else if (testCase == 5) // test solve
    {
        int input[] = {1, 2, 3, 4};
        int size = 4;
        int target = -9;
        int result[ARRAY_MAX_SIZE] = {}; // filled with '\0'
        int resultSize = 0;
        if (solve(input, size, target, result, resultSize))
        {
            cout << "solved: ";
            printArray(result, resultSize);
        }
        else
            cout << "no solution!" << endl;
    }
    else if (testCase == 6) // test solve
    {
        int input[] = {8, 13, 1, 3, 5, 9};
        int size = 6;
        int target = 9;
        int result[ARRAY_MAX_SIZE] = {}; // filled with '\0'
        int resultSize = 0;
        if (solve(input, size, target, result, resultSize))
        {
            cout << "solved: ";
            printArray(result, resultSize);
        }
        else
            cout << "no solution!" << endl;
    }
    else if (testCase == 7) // test solve
    {
        int input[] = {88, 13, 1, 3, 5, 9};
        int size = 6;
        int target = 9;
        int result[ARRAY_MAX_SIZE] = {}; // filled with '\0'
        int resultSize = 0;
        if (solve(input, size, target, result, resultSize))
        {
            cout << "solved: ";
            printArray(result, resultSize);
        }
        else
            cout << "no solution!" << endl;
    }
    else if (testCase == 8) // test solve
    {
        int input[] = {888, 13333, 20000, 1, 99, 3, 5, 9, 33, 44, 55, 100};
        int size = 12;
        int target = -165;
        int result[ARRAY_MAX_SIZE] = {}; // filled with '\0'
        int resultSize = 0;
        if (solve(input, size, target, result, resultSize))
        {
            cout << "solved: ";
            printArray(result, resultSize);
        }
        else
            cout << "no solution!" << endl;
    }

    else if (testCase == 9) // test printString
    {
        printString("1+1-2+1234");
    }
    else if (testCase == 10) // test printString
    {
        printString("Wow this assignment is so much fun!!!");
    }

    else if (testCase == 11) // test getIntValue
    {
        char str[] = "567";
        cout << getIntValue(str, 0, 2) << endl;
    }
    else if (testCase == 12) // test getIntValue
    {
        char str[] = "567";
        cout << getIntValue(str, 0, 1) << endl;
    }
    else if (testCase == 13) // test getIntValue
    {
        char str[] = "567";
        cout << getIntValue(str, 0, 0) << endl;
    }
    else if (testCase == 14) // test getIntValue
    {
        char str[] = "abc567abc";
        cout << getIntValue(str, 4, 5) << endl;
    }

    else if (testCase == 15) // test evaluate
    {
        cout << evaluate("172") << endl;
    }
    else if (testCase == 16) // test evaluate
    {
        cout << evaluate("3+2") << endl;
    }
    else if (testCase == 17) // test evaluate
    {
        cout << evaluate("1+2-4") << endl;
    }                        // 01234
    else if (testCase == 18) // test evaluate
    {
        cout << evaluate("11+21-43") << endl;
    }
    else if (testCase == 19) // test evaluate
    {
        cout << evaluate("11+21-43+888") << endl;
    }
    else if (testCase == 20) // test evaluate
    {
        cout << evaluate("-21") << endl;
    }
    else if (testCase == 21)
    {
        cout << "Find Next :"<<findNext("-21-2", 5, 1) << endl;
        cout << "Find Back :"<<findBack("-2-12", 5, 4) << endl;
    }

    cout << "===================================" << endl;

    return 0;
}
