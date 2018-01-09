#include <iostream>
#include <string>
#include <queue>

using namespace std;

void printTokens(queue<string> tokens) {
    // evaluate the first part, then recurse
    while (!tokens.empty()) {
        string temp = tokens.front();
        tokens.pop();
        cout << temp << endl;
    }
}

bool solveEquation(queue<string> equationTokens, unordered_map<string, bool> valueMap)    {
    // solves the smallest part of the equation possible given what each variable is, then recursively calls itself once again.
    bool ans = true; 
    // don't worry about brackets for now
    string var0 = var1 = lop = "";
    while (!equationTokens.empty()) {
        if (var0 != "") {
            var0 = equationTokens.front();
        } else if (var1 != "")  {
            lop = equationTokens.front();
        } else  {
            var1 = equationTokens.front();
        }
        if (var0 != "" and var1 != "" and lop != "")    {
            evaluate(var0, var1, lop, valueMap, &equationTokens);
            return solveEquation(equationTokens, valueMap);
        }
    }
    return str2bool(var0);
}


queue<string> getTokens(string rawStr)    { // delimiter only needs to be space 
    // not very maintainable bc of this; can't add more delimiters in a very efficient fashion
    queue<string> tokens;
    string token = "";
    for (char c : rawStr)   {
        if (c != ' ')       {
            token += c;
        }   else    {
            if (token != "") tokens.push(token);
            token = "";
        }
    }

    if (token != "")    {
        tokens.push(token);
    }
    return tokens;
}

int main()  {
    queue<string> tokens = getTokens("a s d f");
    solveEquation(tokens);
    return 0;
}
