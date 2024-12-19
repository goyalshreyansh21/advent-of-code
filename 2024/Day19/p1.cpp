#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;

bool isPossible(string& s, unordered_set<string>& set, int i, unordered_map<int, bool>& memo) {
    if(i == s.length())
        return true;
    if(memo.count(i))
        return memo[i];

    for(int j=i+1; j<=s.length(); j++) 
        if(set.count(s.substr(i,j-i)) && isPossible(s, set, j, memo)) 
            return memo[i] = true;

    return memo[i] = false;
}

int main() {
    ifstream inputFile("text.txt");
    string line;

    getline(inputFile, line);
    unordered_set<string> s;
    line += ", ";
    while(line.find(',')!=string::npos) {
        s.insert(line.substr(0,line.find(',')));
        line = line.substr(line.find(',')+2);
    }

    getline(inputFile, line);
    
    int ans = 0;
    unordered_map<int, bool> memo;
    while(getline(inputFile, line)) {
        memo.clear();
        if(isPossible(line, s, 0, memo))
            ans++;
    } 

    cout << ans;

    inputFile.close();
    return 0;
}