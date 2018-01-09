#include <iostream>
#include <string>
#include <deque>
#include <cassert>
#include <unordered_map>

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
        cout << "FAILED! Improper value passed to str2Bool. Asserting true..." << '\n';
        cout << "the value was " << toConvert;
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
        cout << "found lop as and, going to push " << toPush << endl;
    } else if  (lop == "or")   {
        toPush = bool2Str(valueMap[var0] or valueMap[var1]);
    } else if (lop == "->") { 
        toPush = bool2Str(!valueMap[var0] or valueMap[var1]);
    } else  {
        cout << "ERROR! Invalid logical statement. Asserting true...";
        assert(false);
    }
    cout << "evaluate returned " << toPush << " and I'm returning this to be pushed onto deque\n";
    return toPush;
}

bool solveEquationDeque(deque<string> equationTokens, unordered_map<string, bool> valueMap)    {
    // solve equation
    // does not currently support brackets
    string var0 = "", var1 = "", lop = "";
    while (!equationTokens.empty()) {
        if (var0 == "") {
            var0 = equationTokens.front();
            cout << "set var0 to " << var0 << endl;
        } else if (lop == "")  {
            lop = equationTokens.front();
            cout << "set lop to " << lop << endl;
        } else  {
            var1 = equationTokens.front();
            cout << "set var1 to " << var1 << endl;
        }
        equationTokens.pop_front();
        if (var0 != "" and var1 != "" and lop != "")    {
            cout << "evaluating...\n";
            equationTokens.push_front(evaluate(var0, var1, lop, valueMap));
            //printTokens(equationTokens);
            var0 = "";
            var1 = "";
            lop = "";
        }
    }
    return str2Bool(var0);
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

bool solveEquation(string eqn, unordered_map<string, bool> valueMap)    {
    string newEqn = "",toEval = "";
    bool isEval = false;
    if (eqn == "true")  return true;
    if (eqn == "false") return false;
    for (int i = 0; i < eqn.length(); ++i)  {
        char c = eqn[i];
        if (c == '(')   {
            isEval = true;
            toEval = "";
            continue;
        }
        if (c == ')')   {
            newEqn += bool2Str(solveEquationDeque(tokenizeSpaces(toEval), valueMap));
            newEqn += eqn.substr(i+1);
            cout << "newEqn now is " << newEqn << endl;
            return solveEquation(newEqn, valueMap);
            assert(false);
            continue;
        }
        if (isEval) {
            toEval += c;
        } else  {
            newEqn += c;
        }
    }
    // assuming we've broken it into its smallest pieces
    cout << "finally solving " << eqn << endl;
    return solveEquationDeque(tokenizeSpaces(eqn), valueMap);
}



int main()  {
    unordered_map<string, bool> valueMap;
    valueMap["true"] = true;
    valueMap["false"] = false;
    valueMap["a"] = false;
    valueMap["b"] = true;
    valueMap["c"] = false;
    cout << bool2Str(solveEquation("(a -> b) and (a or c)",valueMap));
    return 0;
}
