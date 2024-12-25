#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
using namespace std;

vector<int> helper(vector<string>& temp) {
    vector<int> v(temp[0].size(),-1);
    for(int i=0; i<temp.size(); i++) 
        for(int j=0; j<temp[0].size(); j++) 
            v[j] += (temp[i][j] == '#');
    return v;
}

int main() {
    ifstream inputFile("text.txt");
    string line;

    set<vector<int>> keys, locks;
    vector<string> temp;
    while(getline(inputFile, line)) {
        if(line.empty()) {
            (temp[0][0] == '#' ? locks : keys).insert(helper(temp));
            temp.clear();
            continue;
        }
        temp.push_back(line);
    } 
    (temp[0][0] == '#' ? locks : keys).insert(helper(temp));

    int ans = 0;
    for(vector<int> k:keys) {
        for(vector<int> l:locks) {
            int valid = true;
            for(int i=0; i<k.size() && valid; i++)
                if(k[i]+l[i] > 5)
                    valid = false;
            if(valid)
                ans++;
        }
    }
    cout << ans;

    inputFile.close();
    return 0;
}