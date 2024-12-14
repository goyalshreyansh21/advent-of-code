#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <unordered_set>
using namespace std;

int main() 
{
    ifstream inputFile("text.txt");
    string line;

    int n = 101, m = 103;
    regex pattern(R"(p=(-?[0-9]+),(-?[0-9]+) v=(-?[0-9]+),(-?[0-9]+))");
    smatch match;
    
    vector<unordered_set<string>> v(10000);
    vector<bool> ans(10000, true);

    while(getline(inputFile, line)) {
        regex_search(line, match, pattern);
        int x = stoi(match[1].str());
        int y = stoi(match[2].str());
        int vx = stoi(match[3].str());
        int vy = stoi(match[4].str());

        for(int i=0; i<10000; i++) {
            x = (x+n+vx)%n;
            y = (y+m+vy)%m;
            if(v[i].count(to_string(x)+','+to_string(y)))
                ans[i] = false;
            else  
                v[i].insert(to_string(x)+','+to_string(y));
        }
    }

    for(int i=0; i<ans.size(); i++)
        if(ans[i])
            cout << i+1;

    inputFile.close();
    return 0;
}