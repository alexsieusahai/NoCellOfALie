#include <iostream>
#include <string>
#include <deque>
#include <cassert>
#include <unordered_map>
#include <vector>

#include "printTables.h"

using namespace std;

void printTokens(deque<string> tokens) {
    // evaluate the first part, then recurse
    while (!tokens.empty()) {
        string temp = tokens.front();
        tokens.pop_front();
        cout << temp << endl;
    }
}

bool str2Bool(string toConvert)   {
    if (toConvert == "true")  {
        return true;
    } else if (toConvert == "false")  {
        return false;
    } else  {
        cout << "FAILED! Improper value passed to str2Bool. Asserting false..." << '\n';
        cout << "the value was " << toConvert << endl;
        assert(false);
    }
}

string bool2Str(bool toConvert) {
    if (toConvert == true)  {
        return "true";
    } else if (toConvert == false)  {
        return "false";
    } else  {
        cout << "FAILED! Improper value passed to bool2Str. Asserting true...";
        assert(false);
    }
}

string evaluate(string var0, string var1, string lop, unordered_map<string, bool> valueMap)  {
    string toPush;
    if (lop == "and")   {
        toPush = bool2Str(valueMap[var0] and valueMap[var1]);
        //cout << "found lop as and, going to push " << toPush << endl;
    } else if  (lop == "or")   {
        toPush = bool2Str(valueMap[var0] or valueMap[var1]);
    } else if (lop == "->") { 
        toPush = bool2Str(!valueMap[var0] or valueMap[var1]);
    } else if (lop == "<->")    {
        toPush = bool2Str(valueMap[var0] == valueMap[var1]);
    } else  {
        cout << "ERROR! Invalid logical statement. Asserting true...";
        assert(false);
    }
    //cout << "evaluate returned " << toPush << " and I'm returning this to be pushed onto deque\n";
    return toPush;
}

bool solveEquationDeque(deque<string> equationTokens, unordered_map<string, bool> valueMap)    {
    // solve equation
    // does not currently support brackets
    string var0 = "", var1 = "", lop = "";
    while (!equationTokens.empty()) {
        if (var0 == "") {
            var0 = equationTokens.front();
            //cout << "set var0 to " << var0 << endl;
            // check for NOT
        } else if (lop == "")  {
            lop = equationTokens.front();
            //cout << "set lop to " << lop << endl;
        } else  {
            var1 = equationTokens.front();
            //cout << "set var1 to " << var1 << endl;
        }
        equationTokens.pop_front();
        if (var0 != "" and var1 != "" and lop != "")    {
            //cout << "evaluating...\n";
            equationTokens.push_front(evaluate(var0, var1, lop, valueMap));
            //printTokens(equationTokens);
            var0 = "";
            var1 = "";
            lop = "";
        }
    }
    if (var0 == "true" || var0 == "false")  {
        return str2Bool(var0);
    }
    return valueMap[var0];
}

deque<string> tokenizeSpaces(string rawStr)    { // delimiter only needs to be space 
    // not very maintainable bc of this; can't add more delimiters in a very efficient fashion
    deque<string> tokens;
    string token = "";
    for (char c : rawStr) {
        if (c != ' ')       {
            token += c;
        }   else    {
            if (token != "") tokens.push_back(token);
            token = "";
        }
    }

    if (token != "")    {
        tokens.push_back(token);
    }
    return tokens;
}

bool solveEquation(string eqn, unordered_map<string,bool> valueMap)    {
    bool toReverse = false;
    for (int i = 0; i < eqn.length(); ++i)  {
        char c = eqn[i];
        if (c == '~')   {
            toReverse = true;
            eqn = eqn.substr(eqn.find('~')+1,eqn.length()-1);
            i--;
        }
        if (c == '(')   {
            if (toReverse)  {
                return !solveEquation(eqn.substr(eqn.find('(')+1,eqn.find_last_of(')')-1),valueMap);
            } else  {
                return solveEquation(eqn.substr(eqn.find('(')+1,eqn.find_last_of(')')-1),valueMap);
            }
        }
    }
    bool toReturn = solveEquationDeque(tokenizeSpaces(eqn), valueMap);
    return toReturn;
}

int main()  {
    unordered_map<string, bool> valueMap;
    valueMap["true"] = true;
    valueMap["false"] = false;

    string vars,equation;
    cout << "Please enter your variables below, seperated by a space.\n";
    getline(cin,vars);
    // tokenize vars, and then use the length of that container to get the number of possible states and the number of bits that could represent those possible states
    deque<string> tmp = tokenizeSpaces(vars); 

    // get number of possible states, and the number of bits to represent them
    int numVariations = 1, numBits = tmp.size();
    for (int i = 0; i < numBits; ++i)   {
        numVariations *= 2;
    }


    cout << "Please enter your equation below.\n";
    getline(cin, equation);
    equation = '('+equation+')';
    // should include a syntax checker here 
    
    bool sols[numVariations];
    for (int i = 0; i < numVariations; ++i) {
        // get bits and assign to valueMap appropriately
        for (int j = numBits-1; j >= 0; --j)   {
            if ((i & 1 << j) >> j)  {
                //cout << '1';
                valueMap[tmp[(numBits-1)-j]] = true;
                valueMap["~"+tmp[(numBits-1)-j]] = false;
                cout << tmp[(numBits-1)-j] << " is set to true for this run\n";
            } else  {
                //cout << '0';
                valueMap[tmp[(numBits-1)-j]] = false;
                valueMap["~"+tmp[(numBits-1)-j]] = true;
                cout << tmp[(numBits-1)-j] << " is set to false for this run\n";
            }
        }
        //sols[i] = solveEquation("(a -> b) and (a or c)",valueMap);
        sols[i] = solveEquation(equation,valueMap);
        cout << endl << endl;
        //cout << "sols[i] was set to " << bool2Str(sols[i]) << endl;
    }

    //printMarkdownSyntax(sols, tmp, equation, numVariations, numBits);
    //printLatexSyntax(sols, tmp, equation, numVariations, numBits);
    printPlaintext(sols, tmp, equation, numVariations, numBits);


    //cout << bool2Str(solveEquation("(a -> b) and (a or c)",valueMap));
    return 0;
}
