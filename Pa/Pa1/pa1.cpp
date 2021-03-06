#include <iostream>
using namespace std;

// Global Varibles
const int MAX_INPUT_LEN = 16;      // For Task 1,2,3
const int VALUE_COMPARE_LEN = 5;   // Task 4
const int INPUT_STRAIGHT_LEN = 10; // Task 5
const int MIN_STRAIGHT_LEN = 3;    // Task 5

// Task 1
void cardToNumbers(char cards[], int length, int cards_num[]);
// Task 2
void sortCards(int cards_num[], int length);
// Task 3
bool isContinuous(char cards[], int length, int cards_num[]);
// Task 4
int compareValue(char handA[], char handB[], int &valueA, int &valueB);
// Task 5
int longestStraight(int cards_num[]);

// Task 1
void cardToNumbers(char cards[], int length, int cards_num[])
{
    /*
        Task 1:
        You can assume that the input string array is always valid, the element can only be:
        1. 2 ~ 9 digits
        2. 10(represented by !), J, Q, K, A
        3. JOKER which is represented by *
        We assume:
        1. J, Q, K are 11, 12, 13 respectively
        2. * is 0
        3. ! is 10
        cards_num should store the transferred digits ordered as the cards.
        eg. [A, 2, J, !, *] should be [1, 2, 11, 10, 0]

        Parameters:
            cards: input string array
            length: length of the input array
            cards_num: output array to store the corresponding digits of input array
    */

    // Write your code here
    for (int i = 0; i < length; i++)
    {
        switch (cards[i])
        {
        case 'J':
        {
            cards_num[i] = 11;
            break;
        }

        case 'Q':
        {
            cards_num[i] = 12;
            break;
        }

        case 'K':
        {
            cards_num[i] = 13;
            break;
        }

        case '*':
        {
            cards_num[i] = 0;
            break;
        }

        case '!':
        {
            cards_num[i] = 10;
            break;
        }

        case 'A':
        {
            cards_num[i] = 1;
            break;
        }

        default:
        {
            cards_num[i] = (int)cards[i] - 48;
            break;
        }
        }
    }
}

// Task 2
void sortCards(int cards_num[], int length)
{
    /*
        Task 2:
        You should sort the number array
        You can assume that the input int array is always valid

        Parameters:
            cards_num: input array of cards numbers
            length: length of the input array
    */
    // write your code here
    for (int i = 0; i < length - 1; i++)
        for (int j = 0; j < length - 1 - i; j++)
            if (cards_num[j] > cards_num[j + 1])
                swap(cards_num[j], cards_num[j + 1]);
}

// Task 3

bool isContinuous(char cards[], int length, int cards_num[])
{
    /*
        Task 3:
        You need to check whether the input card array can form a straight.
        A straight is a hand that contains cards of sequential rank:
            eg. [A, 2, 3, 4, 5] or [10, J, Q, K, A]
            but cannot cross from K to 2: eg. [Q, K, A, 2, 3] is invalid
        The longest straight should be from A to A: [A, 2, 3, ..., Q, K, A]
        Notion: At this time, we let JOKER(*) be able to be any cards.

        Parameters:
            cards: input char array containing the cards characters
            length: length of the input array
            cards_num: array to store the corresponding digits of input array, you may use this array to help you to deal with this problem.
                       this array has the same length with cards array.
        Return:
            whether the input is a straight
    */

    // Write your code here
    cardToNumbers(cards, length, cards_num);
    sortCards(cards_num, length);
    bool temp = true;
    int count = 1;
    int jokerCount = 0;
    int repeatCount = 0;
    bool firstJoker = true;
    for (int i = 0; i < length - 1; i++)
        for (int j = 0; j < length - 1 - i; j++)
        {
            repeatCount--;
            if (cards_num[j] == cards_num[i])
                repeatCount++;
        }

    if (repeatCount >= 2)
    {
        // cout << "error 1"<<endl;
        temp = false;
    }
    for (int i = 0; i < length; i++)
    {
        if ((cards_num[i + 1] - cards_num[i] == 1 && cards_num[i] - cards_num[i - 1] == 1) || cards_num[i] == 0 || jokerCount > 0 || cards_num[length - 1] - cards_num[length - 3] == 2 || cards_num[length - 1] - cards_num[length - 2] == 1)
        {
            if (cards_num[i] == 0)
            {
                jokerCount++;
            }
            else if ((cards_num[i + 1] - cards_num[i] != 1 || cards_num[i - 1] - cards_num[i] != -1) && !firstJoker)
            {
                if (i == length - 1)
                {
                }
                else
                {
                    jokerCount--;
                }
            }

            // cout << "Loop:" << i << " Number:" << cards_num[i] <<endl;
            // cout << "jokercount" << jokerCount <<endl;
            count++;
            if (length >= 14)
            {
                if (jokerCount <= 0 && temp != true)
                {
                    // cout << "error 2"<<endl;
                    temp = false;
                }
            }

            if (firstJoker && cards_num[i + 1] - cards_num[i] != 1)
                firstJoker = false;
        }

        else
        {
            if (firstJoker && cards_num[i + 1] - cards_num[i] != 1 || cards_num[i + 1] - cards_num[i] != 0)
                firstJoker = false;

            if (jokerCount < 1)
            {
                // cout << "error 3"<<endl;
                temp = false;
            }
            else
            {
                if (jokerCount <= 0 && temp != true)
                {

                    // cout << "error 4"<<endl;
                    temp = false;
                }
            }
        }
    }
    if (count >= 5 && temp == true)
    {
        return true;
    }
    else
    {
        // cout << "error 5"<<endl;
        return false;
    }
}

// Task 4
int compareValue(char handA[], char handB[], int &valueA, int &valueB)
{
    /*
        Task 4:
        You need compare the values of this two hands.
        Value for a straight is the value of the largest card.
            eg. [10, J, Q, K, A] is the largest straight with value equal to 14
            eg. [A, 2, 3, 4, 5] is the smallest straight with value equal to 5.
            eg. Because jokers can be any cards, for [JOKER, 4, 5, 6, 7], we should consider its highest value as 8 when we set JOKER to be 8;
            eg. Same with above, [JOKER, JOKER, 4, 5, 6] should be considered as [4, 5, 6, 7*, 8*]
        Value for a normal hand is the sum of all cards, at this time, we consider A is 14, JOKER is 15
            eg. [A, 2, 3, JOKER, 6] has 40 value.
        To compare a straight with a normal hand, we consider a straight is always larger than the normal hand.
            eg. [A, 2, 3, 4, 5] is higher than [A, J, J, J, J]

        For this task, we set the length of the handA and handB is always VALUE_COMPARE_LEN.

        Parameters:
            handA: input sequence A of cards
            handB: input sequence B of cards
            valueA: store the value of sequence A
            valueB: store the value of sequence B

        Return:
            1 -> handA is larger than handB;
            0 -> handA is equal to handB;
            -1 -> handA is smaller than handB;
    */

    // Write your code here
    int handA_num[VALUE_COMPARE_LEN];
    int handB_num[VALUE_COMPARE_LEN];
    bool isStraight_A;
    bool isStraight_B;
    isStraight_A = isContinuous(handA, VALUE_COMPARE_LEN, handA_num);
    isStraight_B = isContinuous(handB, VALUE_COMPARE_LEN, handB_num);
    cardToNumbers(handA, VALUE_COMPARE_LEN, handA_num);
    cardToNumbers(handB, VALUE_COMPARE_LEN, handB_num);

    if (isStraight_A && isStraight_B)
    {
        sortCards(handA_num, VALUE_COMPARE_LEN);
        sortCards(handB_num, VALUE_COMPARE_LEN);

        valueA = handA_num[VALUE_COMPARE_LEN - 1];
        if (valueA == 15)
            valueA = handA_num[VALUE_COMPARE_LEN - 2];

        valueB = handB_num[VALUE_COMPARE_LEN - 1];
        if (valueB == 15)
            valueB = handB_num[VALUE_COMPARE_LEN - 2];
    }
    else if (isStraight_A)
    {
        sortCards(handA_num, VALUE_COMPARE_LEN);

        valueA = handA_num[VALUE_COMPARE_LEN - 1];
        if (valueA == 15)
            valueA = handA_num[VALUE_COMPARE_LEN - 2];

        for (int i = 0; i < VALUE_COMPARE_LEN; i++)
        {
            switch (handB_num[i])
            {
            case 0:
            {
                handB_num[i] = 15;
                break;
            }

            case 1:
            {
                handB_num[i] = 14;
                break;
            }

            default:
                break;
            }
        }

        for (int k = 0; k < VALUE_COMPARE_LEN; k++)
        {
            valueB += handB_num[k];
        }
        return 1;
    }
    else if (isStraight_B)
    {
        sortCards(handB_num, VALUE_COMPARE_LEN);

        valueB = handB_num[VALUE_COMPARE_LEN - 1];
        if (valueB == 15)
            valueB = handB_num[VALUE_COMPARE_LEN - 2];

        for (int i = 0; i < VALUE_COMPARE_LEN; i++)
        {
            switch (handA_num[i])
            {
            case 0:
            {
                handA_num[i] = 15;
                break;
            }

            case 1:
            {
                handA_num[i] = 14;
                break;
            }

            default:
                break;
            }
        }

        for (int k = 0; k < VALUE_COMPARE_LEN; k++)
        {
            valueA += handA_num[k];
        }
        return -1;
    }
    else
    {
        for (int i = 0; i < VALUE_COMPARE_LEN; i++)
        {

            switch (handA_num[i])
            {
            case 0:
            {
                handA_num[i] = 15;
                break;
            }

            case 1:
            {
                handA_num[i] = 14;
                break;
            }

            default:
                break;
            }

            switch (handB_num[i])
            {
            case 0:
            {
                handB_num[i] = 15;
                break;
            }

            case 1:
            {
                handB_num[i] = 14;
                break;
            }

            default:
                break;
            }
        }
        for (int j = 0; j < VALUE_COMPARE_LEN; j++)
        {
            valueA += handA_num[j];
        }
        for (int k = 0; k < VALUE_COMPARE_LEN; k++)
        {
            valueB += handB_num[k];
        }
    }
    if (valueA > valueB)
    {
        return 1;
    }
    else if (valueA < valueB)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

// Task 5
int longestStraight(int cards_num[])
{
    /*
        Task 5:
        Given a cards number array, find the longest straight.
        If there are several straight with the same longest length, choose the straight with highest value.
        The value for a straight is the value of the largest cards num. For [10, J, Q, K, A], the value is 14
        The length of the
        Parameters:
            cards_num: input sorted cards number array without Jokers
        Return:
            length k of the longest straight
        After running:
            cards_num: first k elements forms the longest straight with ascending order,
                       the left elements are put on the right with ascending order
    */

    // Write your code here
}

// DO NOT WRITE ANYTHING AFTER THIS LINE. ANYTHING AFTER THIS LINE WILL BE REPLACED.
// Helper Function
int getInput(char cards[], int max_length)
{
    cout << "Please type the cards one by one. All characters should be CAPITAL. And press ENTER. '.' for finish(only for task 1,2,3)" << endl;
    int index = 0;
    int length = 0;
    while (true)
    {
        cout << "The " << index + 1 << " input:";
        cin >> cards[index];

        if (cards[index] == '.')
        {
            break;
        }
        index++;
        length++;
        if (length >= max_length)
        {
            break;
        }
    }
    return length;
}

void printNums(int cards_num[], int length)
{
    cout << "cards numbers are: ";
    for (int i = 0; i < length; ++i)
    {
        cout << cards_num[i];
        if (i != length - 1)
        {
            cout << ", ";
        }
    }
    cout << endl;
}

void printChar(char cards[], int length)
{
    cout << "cards are: ";
    for (int i = 0; i < length; ++i)
    {
        cout << cards[i];
        if (i != length - 1)
        {
            cout << ", ";
        }
    }
    cout << endl;
}

int main()
{
    bool finish = false;
    cout << "Poker Staright Game started!" << endl;
    while (!finish)
    {
        cout << "Choose your tasks:" << endl;
        cout << "Task 1: change cards to numbers" << endl;
        cout << "Task 2: sort " << endl;
        cout << "Task 3: is continuous" << endl;
        cout << "Task 4: compare two hands" << endl;
        cout << "Task 5: find longest straight" << endl;
        cout << "Task 6: close the program" << endl;
        cout << "Input your desicion" << endl;
        int choice = 0;
        cin >> choice;
        cout << "\nYou choose the task " << choice << endl;

        // Task 1,2,3,5 variables
        char cards[MAX_INPUT_LEN];
        int cards_num[MAX_INPUT_LEN];

        // Task 4 variables
        char task4A[VALUE_COMPARE_LEN];
        char task4B[VALUE_COMPARE_LEN];
        int task4A_num[VALUE_COMPARE_LEN], task4B_num[VALUE_COMPARE_LEN];
        int valueA, valueB;

        bool check;                 // task 3
        int lengthA, lengthB, comp; // task 4
        int longest = 0;            // task 5

        int length = 0;
        switch (choice)
        {
        case 6:
            cout << "Close the program" << endl;
            break;

        case 1:
            length = getInput(cards, 20);
            cardToNumbers(cards, length, cards_num);
            cout << "Input cards: ";
            printChar(cards, length);
            cout << "Transferred digits: ";
            printNums(cards_num, length);
            break;

        case 2:
            length = getInput(cards, 20);
            cardToNumbers(cards, length, cards_num);
            cout << "Before sorting, ";
            printNums(cards_num, length);
            sortCards(cards_num, length);
            cout << "After sorting, ";
            printNums(cards_num, length);
            break;

        case 3:
            length = getInput(cards, 20);
            cout << "Input ";
            printChar(cards, length);
            check = isContinuous(cards, length, cards_num);
            cout << boolalpha << "This hand is " << ((check) ? "Indeed" : "NOT") << " a straight" << endl;
            break;

        case 4:
            cout << "For this task, you should input only " << VALUE_COMPARE_LEN << " numbers for each input" << endl;
            cout << "Input A." << endl;
            lengthA = getInput(task4A, VALUE_COMPARE_LEN);
            printChar(task4A, lengthA);
            cout << "Input B." << endl;
            lengthB = getInput(task4B, VALUE_COMPARE_LEN);
            printChar(task4B, lengthB);
            if (lengthA != 5 || lengthB != 5)
            {
                cerr << "The inputs are wrong." << endl;
                break;
            }
            comp = compareValue(task4A, task4B, valueA, valueB);
            cout << "Value of hand A is: " << valueA << endl;
            cout << "Value of hand B is: " << valueB << endl;
            if (comp == 1)
            {
                cout << "Input A is larger than Input B" << endl;
            }
            else if (comp == 0)
            {
                cout << "Input A is equal to Input B" << endl;
            }
            else
            {
                cout << "Input A is smaller than Input B" << endl;
            }
            break;

        case 5:
            cout << "For this task, you should input only " << INPUT_STRAIGHT_LEN << " numbers for each input" << endl;
            cout << "At this task, you can not input JOKER." << endl;
            length = getInput(cards, INPUT_STRAIGHT_LEN);
            cardToNumbers(cards, INPUT_STRAIGHT_LEN, cards_num);
            printNums(cards_num, INPUT_STRAIGHT_LEN);
            longest = longestStraight(cards_num);
            cout << "The longest straight ";
            printNums(cards_num, longest);
            cout << "Whole array ";
            printNums(cards_num, INPUT_STRAIGHT_LEN);
            break;

        default:
            cerr << "Wrong decision! Program done!" << endl;
            break;
        }
        cout << endl
             << endl;
        if (choice == 6)
        {
            break;
        }
    }
    return 0;
}