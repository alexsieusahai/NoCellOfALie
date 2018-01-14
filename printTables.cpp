#include "printTables.h"
#include <string>
#include <unordered_map>

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
        cout << spacesForCentering; // << truthArray[i] << endl;
        (truthArray[i]) ? cout << "T" : cout << "F";
        cout << endl;
        if (i != numVariations-1)   cout << "| ";
    }
    cout << endl << endl << endl;
}

string toLatex(string equation) {
    unordered_map<string, string> latexMap;
    latexMap["and"] = "\\land";
    latexMap["or"] = "\\lor";
    latexMap["~"] = "\\neg";
    latexMap["->"] = "\\to";
    /* Converts equation in formatting to be read by program into LaTeX syntax
     * ARGS:
     * equation is a string which is formatted to be the equation that I have used for the rest of the prog
     * RETURNS:
     * equation in LaTeX syntax
     */
    string token = "";
    string newEquation = "";
    for (int i = 0; i < equation.length(); ++i) {
        char c = equation[i];
        if (c == ' ')   {
            if (latexMap.count(token))  {
                newEquation += latexMap[token]+" ";
            } else  {
                newEquation += token+" ";
            }
            token = "";
        } else if (c == '~')    {
            newEquation += latexMap["~"]+" ";
        } else  {
            token += c;
        }
    }
    if (latexMap.count(token))  {
        newEquation += latexMap[token];
    } else  {
        newEquation += token;
    }
    return newEquation;
}

void printLatexSyntax(bool truthArray[], deque<string> vars, string equation,int numVariations, int numBits) {
    cout << "Note that the below code requires this at the beginning of the document: \n" 
        << "\\usepackage{amsmath}\n" 
        << "\\usepackage{array}\n"
        <<"\\newcolumntype{C}{>$c<$}\n";
    cout << "LaTeX syntax below: \n\n";
    cout << "\\begin{array}{";
    for (int i = 0; i < numBits; ++i)   {
        cout << "C|";
    }
    cout << "C}\n";
    while (!vars.empty())   {
            cout << '$' << vars.front() << "$ & ";
            vars.pop_front();
    }
    cout << '$' << toLatex(equation) << "$ \\\\ \n"
        << "\\hline \n";
    for (int i = 0; i < numVariations; ++i) {
        // get the bits of i below
        for (int j = 0; j < numBits; ++j)   {
            ((i & 1 << j) >> j) ? cout << "T " : cout << "F ";
            cout << "& ";
        }
        // now output the logical answer for the equation
        (truthArray[i]) ? cout << "T " : cout << "F ";
        cout << "\\\\ \n";
    }
    cout << "\\end{array}\n \n";
}

void printMarkdownSyntax(bool truthArray[], deque<string> vars, string equation,int numVariations, int numBits) {
    cout << "Markdown syntax below: \n \n";
    // print out the beginning
    while (!vars.empty())   {
        cout << vars.front() << " | ";
        vars.pop_front();
    }
    cout << equation << endl;

    for (int i = 0; i < numBits; ++i)   {
        cout << "----|"; // for each column
    }
    cout << "----\n";
    
    for (int i = 0; i < numVariations; ++i) {
        // get the bits of i below
        for (int j = 0; j < numBits; ++j)   {
            ((i & 1 << j) >> j) ? cout << "T " : cout << "F ";
            cout << "| ";
        }
        // now output the logical answer for the equation
        (truthArray[i]) ? cout << "T" : cout << "F";
        cout << "\n";
    }
}
