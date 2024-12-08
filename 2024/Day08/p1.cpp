#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

bool isvalid(vector<string>& grid, int x, int y) {
    return (x>=0 && x<grid.size() && y>=0 && y<grid[0].length());
}

void mark(vector<string>& grid, char c, unordered_set<string>& ans) {
    vector<pair<int,int>> v;
    for(int i=0; i<grid.size(); i++) 
        for(int j=0; j<grid[0].length(); j++) 
            if(grid[i][j] == c)
                v.push_back({i,j});

    for(int i=0; i<v.size(); i++) {
        for(int j=i+1; j<v.size(); j++) {
            int xdiff = v[i].first-v[j].first, ydiff = v[i].second-v[j].second;
            
            int x = v[i].first+xdiff, y = v[i].second+ydiff;
            if(isvalid(grid, x, y)) 
                ans.insert(to_string(x) + ',' + to_string(y));

            x = v[j].first-xdiff, y = v[j].second-ydiff;
            if(isvalid(grid, x, y)) 
                ans.insert(to_string(x) + ',' + to_string(y));
        }
    }
    return;
}

int main() {
    ifstream inputFile("text.txt");
    string line;
    vector<string> grid;

    while(getline(inputFile, line)) 
        grid.push_back(line);

    unordered_set<string> ans;
    for(int i=0; i<10; i++)
        mark(grid, '0'+i, ans);
    for(int i=0; i<26; i++)
        mark(grid, 'A'+i, ans);
    for(int i=0; i<26; i++)
        mark(grid, 'a'+i, ans);
    
    cout<<ans.size();

    inputFile.close();
    return 0;
}