
int main()
{
    int testCase;
    cout << "Hi, recursion master! Which test case do you want to run?" << endl;
    cin >> testCase;

    {
        cout << endl << "Test case " << testCase << " output:" << endl;
        cout << "===================================" << endl;
        if(testCase == 0) //this test case is used to show you how printArray works; it is NOT used to grade your work and it is NOT on ZINC
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
        
        else if(testCase == 1) //test arraySum
        {
            int array[] = {1, 2, 3};
            cout << arraySum(array, 3) << endl;
        }
        else if(testCase == 2) //test arraySum
        {
            int array[] = {-1, -234, 33, 5};
            cout << arraySum(array, 4) << endl;
        }
        else if(testCase == 3) //test arraySum (hidden)
        {
            int array[] = {-101010};
            cout << arraySum(array, 1) << endl;
        }
        else if(testCase == 4) //test arraySum (hidden)
        {
            int array[] = {1999, 2, 3, -4, 5, 6, 7, 8, -9, 10, -9999, 1024};
            cout << arraySum(array, 12) << endl;
        }

        else if(testCase == 5) //test solve
        {
            int input[] = {1, 2, 3, 4};
            int size = 4;
            int target = 2;
            int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
            int resultSize = 0;
            if(solve(input, size, target, result, resultSize))
            {
                cout << "solved: ";
                printArray(result, resultSize);
            }
            else
                cout << "no solution!" << endl;
        }
        else if(testCase == 6) //test solve
        {
            int input[] = {1, 2, 3, 4};
            int size = 4;
            int target = -2;
            int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
            int resultSize = 0;
            if(solve(input, size, target, result, resultSize))
            {
                cout << "solved: ";
                printArray(result, resultSize);
            }
            else
                cout << "no solution!" << endl;
        }
        else if(testCase == 7) //test solve
        {
            int input[] = {1, 2, 3, 4};
            int size = 4;
            int target = -9;
            int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
            int resultSize = 0;
            if(solve(input, size, target, result, resultSize))
            {
                cout << "solved: ";
                printArray(result, resultSize);
            }
            else
                cout << "no solution!" << endl;
        }
        else if(testCase == 8) //test solve
        {
            int input[] = {8, 13, 1, 3, 5, 9};
            int size = 6;
            int target = 9;
            int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
            int resultSize = 0;
            if(solve(input, size, target, result, resultSize))
            {
                cout << "solved: ";
                printArray(result, resultSize);
            }
            else
                cout << "no solution!" << endl;
        }
        else if(testCase == 9) //test solve
        {
            int input[] = {88, 13, 1, 3, 5, 9};
            int size = 6;
            int target = 9;
            int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
            int resultSize = 0;
            if(solve(input, size, target, result, resultSize))
            {
                cout << "solved: ";
                printArray(result, resultSize);
            }
            else
                cout << "no solution!" << endl;
        }
        else if(testCase == 10) //test solve
        {
            int input[] = {888, 13333, 20000, 1, 99, 3, 5, 9, 33, 44, 55, 100};
            int size = 12;
            int target = -165;
            int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
            int resultSize = 0;
            if(solve(input, size, target, result, resultSize))
            {
                cout << "solved: ";
                printArray(result, resultSize);
            }
            else
                cout << "no solution!" << endl;
        }
        else if(testCase == 11) //test solve (hidden)
        {
            int input[] = {888, 13, 1, 3, 5, 9, 33, 44, 55, 100};
            int size = 10;
            int target = 155;
            int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
            int resultSize = 0;
            if(solve(input, size, target, result, resultSize))
            {
                cout << "solved: ";
                printArray(result, resultSize);
            }
            else
                cout << "no solution!" << endl;
        }
        else if(testCase == 12) //test solve (hidden)
        {
            int input[] = {888, 13333, 20000, 1, 99, 3, 5, 9, 33, 44, 55, 100};
            int size = 12;
            int target = -265;
            int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
            int resultSize = 0;
            if(solve(input, size, target, result, resultSize))
            {
                cout << "solved: ";
                printArray(result, resultSize);
            }
            else
                cout << "no solution!" << endl;
        }
        else if(testCase == 13) //test solve (hidden)
        {
            int input[] = {888};
            int size = 1;
            int target = -888;
            int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
            int resultSize = 0;
            if(solve(input, size, target, result, resultSize))
            {
                cout << "solved: ";
                printArray(result, resultSize);
            }
            else
                cout << "no solution!" << endl;
        }
        else if(testCase == 14) //test solve (hidden)
        {
            int input[] = {889};
            int size = 1;
            int target = -888;
            int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
            int resultSize = 0;
            if(solve(input, size, target, result, resultSize))
            {
                cout << "solved: ";
                printArray(result, resultSize);
            }
            else
                cout << "no solution!" << endl;
        }
        else if(testCase == 15) //test solve (hidden)
        {
            int input[] = {1, 2};
            int size = 2;
            int target = 0;
            int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
            int resultSize = 0;
            if(solve(input, size, target, result, resultSize))
            {
                cout << "solved: ";
                printArray(result, resultSize);
            }
            else
                cout << "no solution!" << endl;
        }
        else if(testCase == 16) //test solve (hidden)
        {
            int input[] = {1,2,3,4,5,999};
            int size = 6;
            int target = 999;
            int result[ARRAY_MAX_SIZE] = {}; //filled with '\0'
            int resultSize = 0;
            if(solve(input, size, target, result, resultSize))
            {
                cout << "solved: ";
                printArray(result, resultSize);
            }
            else
                cout << "no solution!" << endl;
        }

        else if(testCase == 17) //test printString
        {
            printString("1+1-2+1234");
        }
        else if(testCase == 18) //test printString
        {
            printString("Wow this assignment is so much fun!!!");
        }
        else if(testCase == 19) //test printString (hidden)
        {
            printString(""); //empty string is also a valid C-string
        }
        else if(testCase == 20) //test printString (hidden)
        {
            printString("loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong");
        }

        else if(testCase == 21) //test getIntValue
        {
            char str[] = "567";
            cout << getIntValue(str, 0, 2) << endl;
        }
        else if(testCase == 22) //test getIntValue
        {
            char str[] = "567";
            cout << getIntValue(str, 0, 1) << endl;
        }
        else if(testCase == 23) //test getIntValue
        {
            char str[] = "567";
            cout << getIntValue(str, 0, 0) << endl;
        }
        else if(testCase == 24) //test getIntValue
        {
            char str[] = "abc567abc";
            cout << getIntValue(str, 4, 5) << endl;
        }
        else if(testCase == 25) //test getIntValue (hidden)
        {
            char str[] = "56712340";
            cout << getIntValue(str, 0, 7) << endl;
        }
        else if(testCase == 26) //test getIntValue (hidden)
        {
            char str[] = "x0x";
            cout << getIntValue(str, 1, 1) << endl;
        }
        else if(testCase == 27) //test getIntValue (hidden)
        {
            char str[] = "x1000x";
            cout << getIntValue(str, 1, 4) << endl;
        }
        else if(testCase == 28) //test getIntValue (hidden)
        {
            char str[] = "abc2147483647abc2147483647abc";
            cout << getIntValue(str, 16, 25) << endl;
        }

        else if(testCase == 29) //test evaluate
        {
            cout << evaluate("172") << endl;
        }
        else if(testCase == 30) //test evaluate
        {
            cout << evaluate("3+2") << endl;
        }
        else if(testCase == 31) //test evaluate
        {
            cout << evaluate("1+2-4") << endl;
        }
        else if(testCase == 32) //test evaluate
        {
            cout << evaluate("11+21-43") << endl;
        }
        else if(testCase == 33) //test evaluate
        {
            cout << evaluate("11+21-43+888") << endl;
        }
        else if(testCase == 34) //test evaluate
        {
            cout << evaluate("-21") << endl;
        }
        else if(testCase == 35) //test evaluate (hidden)
        {
            cout << evaluate("-172-123123") << endl;
        }
        else if(testCase == 36) //test evaluate (hidden)
        {
            cout << evaluate("-172-123123+1289312-123213+1") << endl;
        }
        else if(testCase == 37) //test evaluate (hidden)
        {
            cout << evaluate("-1-2-3-1-2-3-4-1-2-4-4-1-2-4-5-1-2-5-1-5-1-5-1-1-2-4-5-6-7-7-7-7-7") << endl;
        }
        else if(testCase == 38) //test evaluate (hidden)
        {
            cout << evaluate("-12341-12342-12343-12341-12342-12343-12344-12341-12342-12344-12344-12341-12342-12344-12345-12341-12342-12345-12341-12345-12341-12345-12341-12341-12342-12344-12345-12346-12347-12347-12347-12347-12347") << endl;
        }
        else if(testCase == 39) //test evaluate (hidden)
        {
            cout << evaluate("12341+12342+12343+12341+12342+12343+12344+12341+12342+12344+12344+12341+12342+12344+12345+12341+12342+12345+12341+12345+12341+12345+12341+12341+12342+12344+12345+12346+12347+12347+12347+12347+12347") << endl;
        }
        else if(testCase == 40) //test evaluate (hidden)
        {
            cout << evaluate("2147483647-2147483647+2147483647") << endl;
        }
        cout << "===================================" << endl;
    }

    return 0;
}
