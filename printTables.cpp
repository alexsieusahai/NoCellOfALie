#include "printTables.h"
#include <string>

using namespace std;

void printPlaintext(bool truthArray[], deque<string> vars, string equation,int numVariations, int numBits) {
    cout << "| ";
    int numLines = 2;
    while (!vars.empty())   {
        cout << vars.front() << " | ";
        numLines += vars.front().length() + 3;
        vars.pop_front();
    }
    cout << equation << endl;
    numLines += equation.length();
    for (int i = 0 ; i < numLines; ++i) {
        cout << '-';
    }
    cout << endl << "| ";

    // finding the amount to add to place the bool value near the middle of the equation
    string spacesForCentering = "";
    for (int i = 0; i < equation.length()/2; ++i) {
        spacesForCentering += ' '; 
    }

    for (int i = 0; i < numVariations; ++i) {
        for (int j = numBits-1; j >= 0; --j)    {
            if ((i & 1 << j) >> j)  {
                cout << "T" << " | ";
            } else  {
                cout << "F" << " | ";
            }
        }
        cout << spacesForCentering << truthArray[i] << endl;
        if (i != numVariations-1)   cout << "| ";
    }
}
