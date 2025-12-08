#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <functional>
using namespace std;

unordered_map<string, function<int(int, int)>> operation;

long long dfs(string s, unordered_map<string, vector<string>>& m, unordered_map<string, int>& val) {
    if(val.count(s))
        return val[s];
    
    int n1 = dfs(m[s][0], m, val);
    int n2 = dfs(m[s][1], m, val);
    return val[s] = operation[m[s][2]](n1, n2);
}

int main() {
    ifstream inputFile("text.txt");
    string line;

    unordered_map<string, int> val;
    while(getline(inputFile, line) && !line.empty()) 
        val[line.substr(0,3)] = line.back()-'0';
    
    unordered_map<string, vector<string>> m;
    unordered_set<string> gates;
    while(getline(inputFile, line)) {
        string in1 = line.substr(0,3);
        
        line = line.substr(4);
        string op = line.substr(0,line.find(' '));
        
        line = line.substr(line.find(' ')+1);
        string in2 = line.substr(0,3);

        string out = line.substr(7);
        m[out] = {in1,in2,op};
        if(out[0] == 'z')
            gates.insert(out);
    }

    operation["AND"] = [](int a, int b) { return a && b; };
    operation["OR"] = [](int a, int b) { return a || b; };
    operation["XOR"] = [](int a, int b) { return a != b; }; 

    long long ans = 0;
    for(string g:gates) 
        ans |= dfs(g, m, val)<<stoll(g.substr(1));

    cout << ans;

    inputFile.close();
    return 0;
}