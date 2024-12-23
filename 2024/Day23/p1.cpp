#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
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

    unordered_set<string> ans;
    for(pair<const string, vector<string>>& p:m) {
        if(p.first[0] == 't') {
            for(int i=0; i<p.second.size(); i++) {
                for(int j=i+1; j<p.second.size(); j++) {
                    string n1 = p.second[i], n2 = p.second[j];
                    if(find(begin(m[n1]), end(m[n1]), n2) != end(m[n1])) {
                        vector<string> v = {p.first, n1, n2};
                        sort(v.begin(), v.end());
                        ans.insert(v[0]+v[1]+v[2]);
                    }
                }
            }
        }
    }

    cout << ans.size();

    inputFile.close();
    return 0;
}