#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    ifstream inputFile("text.txt");
    string line;

    unordered_map<string, vector<string>> m;
    while(getline(inputFile, line)) {
        string n1 = line.substr(0, line.find('-')), n2 = line.substr(line.find('-')+1);
        m[n1].push_back(n2);
        m[n2].push_back(n1);
    } 

    vector<string> v;
    for(pair<const string, vector<string>>& p:m) {
        vector<string> neighbors = {p.first};
        
        for(int i=0; i<p.second.size(); i++) {
            bool canadd = true;

            for(string& s:neighbors) {
                if(find(begin(m[s]), end(m[s]), p.second[i]) == end(m[s])) {
                    canadd = false;
                    break;
                }
            }
            if(canadd)
                neighbors.push_back(p.second[i]);
        }
        
        if(neighbors.size() > v.size()) 
            v = neighbors;
    }

    sort(v.begin(), v.end());
    string ans;
    for(string s:v)
        ans += s + ',';
    ans.pop_back();
    cout << ans;

    inputFile.close();
    return 0;
}