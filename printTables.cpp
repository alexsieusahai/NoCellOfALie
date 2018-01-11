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

string toLatex(string equation) {
    /* Converts equation in formatting to be read by program into LaTeX syntax
     * TODO: Get it done
     * ARGS:
     * equation is a string which is formatted to be the equation that I have used for the rest of the prog
     * RETURNS:
     * equation in LaTeX syntax
     */

    return equation;
}

void printLatexSyntax(bool truthArray[], deque<string> vars, string equation,int numVariations, int numBits) {
    cout << "\\begin{array}{";
    for (int i = 0; i < numBits; ++i)   {
        cout << "C|";
    }
    cout << "C}\n";
    while (!vars.empty())   {
            cout << '$' << vars.front() << "$ & ";
            vars.pop_front();
    }
    cout << '$' << toLatex(equation) << "$ \\\\$ \n"
        << "\\hline \n";
    for (int i = 0; i < numVariations; ++i) {
        // get the bits of i below
        for (int j = 0; j < numBits; ++j)   {
            ((i & 1 << j) >> j) ? cout << "T " : cout << "F ";
            cout << "& ";
        }
        // now output the logical answer for the equation
        cout << "& ";
        (truthArray[i]) ? cout << "T" : cout << "F";
        cout << "\\\\ \n";
    }
    cout << "\\end{array}\n";
}
