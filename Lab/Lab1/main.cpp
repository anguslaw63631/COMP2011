#include <iostream>
using namespace std;
  
int main()
{
    /*
        There are 4 errors in total. Can you catch them all? :)
  
        See the expected output section on the lab page to see what is expected from the corrected program.
    */
  
    int number;//missing ;
    cout << "Welcome to the exciting, fun, and awesome programming world! "
         << "Enter an odd number, and I can tell something about you! "<< endl;//missing <<
    cin >> number;
  
    if (number % 2 == 0) //replace = with ==
        cout << "Hmm... this is not an odd number..." << endl;
    else
    {
        if (number < 0)
            cout << "You seem to be a bit negative... :( Cheer up! " << endl;
        else
            cout << "You must be very excited! Me too! :)" << endl;
    }//missing }
    return 0;
}

/*
Line 12 missing ;
Line 14 missing <<
Line 17 replace = with ==
Line 25 missing }
*/
