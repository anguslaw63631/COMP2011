#include <iostream>
#include <cmath>

using namespace std;
const int NUM_HOUSES = 8;

void print_houses(int houses[], int cur_pos, int night)
{
    // Task 3:
    //   print the state of each house in current night.
    //   '*': thief's position, '1, 2, 3, ...': stolen houses, '0': valid houses.
    // example:
    //   Night 1:
    //      | 0 | 0 | * | 0 | 0 | 0 | 0 | 0 |
    cout << "Night " << night << ":  " << endl;
    for (int i = 0; i < NUM_HOUSES; i++)
    {
        char temp;
        if (i != cur_pos)
        {
            temp = houses[i] + 48;
        }
        else
        {
            temp = '*';
        }

        cout << "|" << temp;
    }
    cout << "|" << endl;
}

int steal_house(int houses[], int cur_pos, int alert_dis, int night)
{
    // Task 2:
    //   output the next target. When there is no valid house to steal, return -1.
    int target = -1;
    houses[cur_pos] = night - 1;
    for (int i = 0; i < NUM_HOUSES; i++)
    {
        if (houses[i] == 0)
        {
            if (i >= cur_pos + alert_dis)
            {
                target = i - cur_pos;
          
                if (target + cur_pos >= cur_pos + alert_dis || target + cur_pos <= cur_pos - alert_dis)
                {
                    if( houses[cur_pos+target+1] != 0 && alert_dis>2){
                        return -1;
                    }
                    return target;
                }
            }
        }
    }
    for (int i = 0; i < NUM_HOUSES; i++)
    {
        if (houses[i] == 0)
        {
            if (i <= cur_pos - alert_dis)
            {
                target = i - cur_pos + NUM_HOUSES;
                if (target + cur_pos >= cur_pos + alert_dis || target + cur_pos <= cur_pos - alert_dis)
                {
                    return target;
                }
            }
        }
    }
    return -1;
}

int main()
{
    int houses[NUM_HOUSES] = {0};
    int first_target;
    int alert_dis;

    cout << endl
         << "The number of houses in this community is " << NUM_HOUSES << "." << endl;
    // input the first target house ID of the thief (current position) and
    // the alert distance (min interval) of the security system.
    cout << "Please input the first target house ID of the thief: " << endl;
    cin >> first_target;
    while ((first_target >= NUM_HOUSES) || (first_target < 0))
    {
        cout << "The target of the thief should less than " << NUM_HOUSES << endl;
        cout << "Please re-input the first target ID: " << endl;
        cin >> first_target;
    }
    houses[first_target] = 1; // Set first target to 1

    cout << "Please input the alert distance of the community's security system: " << endl;
    cin >> alert_dis;
    while ((alert_dis >= NUM_HOUSES) || (alert_dis < 0))
    {
        cout << "The alert distance of the community's security system should less than " << NUM_HOUSES << endl;
        cout << "Please re-input the alert distance: " << endl;
        cin >> alert_dis;
    }
    cout << endl;

    int cur_pos = first_target;
    int night = 1;
    print_houses(houses, cur_pos, night);
    int temp = cur_pos;
    while (true)
    {
        // Task 1:
        //   - update 'night'
        //   - call 'steal_house( )' function to get the thief's next target and update 'cur_pos'
        //   - call 'print_houses( )' function to print the states of the houses
        //   - When the next target is invalid (steal_house( ) return '-1'), break out the while loop.
        night++;
        temp = cur_pos + steal_house(houses, cur_pos, alert_dis, night);
        if (steal_house(houses, cur_pos, alert_dis, night) == -1)
            break;
        if (temp >= NUM_HOUSES)
            cur_pos = temp - NUM_HOUSES;
        else
            cur_pos = temp;
        print_houses(houses, cur_pos, night);
    }
    cout << endl
         << "No house can be stolen." << endl
         << "Finished." << endl;
}