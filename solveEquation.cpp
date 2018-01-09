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
        assert(true);
    }
}

string bool2Str(bool toConvert) {
    if (toConvert == true)  {
        return "true";
    } else if (toConvert == false)  {
        return "false";
    } else  {
        cout << "FAILED! Improper value passed to bool2Str. Asserting true...";
        assert(true);
    }
}

string evaluate(string var0, string var1, string lop, unordered_map<string, bool> valueMap)  {
    string toPush;
    if (lop == "and")   {
        toPush = bool2Str(valueMap[var0] and valueMap[var1]);
        cout << "found lop as and, going to push " << toPush << endl;
    } else if  (lop == "or")   {
        toPush = bool2Str(valueMap[var0] or valueMap[var1]);
    //} else if (lop == "->") { what's the logical equivalent in AND and OR and NOT?
    } else  {
        cout << "ERROR! Invalid logical statement. Asserting true...";
        assert(true);
    }
    cout << "evaluate returned " << toPush << " and I'm returning this to be pushed onto deque\n";
    return toPush;
}

bool solveEquation(deque<string> equationTokens, unordered_map<string, bool> valueMap)    {
    // solves the smallest part of the equation possible given what each variable is, then recursively calls itself once again.
    // don't worry about brackets for now
    string var0 = "", var1 = "", lop = "";
            return solveEquation(equationTokens, valueMap);
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


deque<string> getTokens(string rawStr)    { // delimiter only needs to be space 
    // not very maintainable bc of this; can't add more delimiters in a very efficient fashion
    deque<string> tokens;
    string token = "";
    for (char c : rawStr)   {
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

int main()  {
    unordered_map<string, bool> valueMap;
    valueMap["a"] = true;
    valueMap["b"] = false;
    valueMap["c"] = true;
    deque<string> tokens = getTokens("a and b and c");
    cout << bool2Str(solveEquation(tokens,valueMap));
    return 0;
}
