#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

int area(vector<vector<int>>& v, int n) {
    int c = 0;
    for(vector<int>& f:v) 
        for(int& i:f) 
            if(i == n)
                c++;
    return c;
}

int perimeter(vector<vector<int>>& v, int n) {
    int c = 0;
    for(int i=0; i<v.size(); i++) {
        if(v[i][0] == n)
            c++;
        for(int j=1; j<v[0].size(); j++) 
            if(v[i][j] == n && v[i][j-1] != n)
                c++;
    }
    for(int j=0; j<v.size(); j++) {
        if(v[0][j] == n)
            c++;
        for(int i=1; i<v[0].size(); i++) 
            if(v[i][j] == n && v[i-1][j] != n)
                c++;
    }
    return c<<=1;
}

int main() 
{
    ifstream inputFile("text.txt");
    string line;
    vector<string> grid;
    
    while(getline(inputFile, line))
        grid.push_back(line);

    int ans = 0;

    vector<vector<int>> directions = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    vector<vector<int>> farmtype(grid.size(), vector<int>(grid[0].length(),-1));
    for(int i=0, f=0; i<grid.size(); i++) {
        for(int j=0; j<grid[0].length(); j++) {
            if(farmtype[i][j] == -1) {
                char c = grid[i][j];
                farmtype[i][j] = f;

                queue<pair<int,int>> q;
                q.push({i,j});
                while(!q.empty()) {
                    int x = q.front().first, y = q.front().second;
                    q.pop();

                    for(vector<int>& dir:directions) {
                        int dx = x + dir[0], dy = y + dir[1];
                        if(dx >= 0 && dx < grid.size() && dy >= 0 && dy < grid[0].length() && grid[dx][dy] == c && farmtype[dx][dy] == -1) {
                            farmtype[dx][dy] = f;
                            q.push({dx,dy});
                        }
                    }
                }
                ans += area(farmtype, f) * perimeter(farmtype, f);
                f++;
            }
        }
    }

    cout << ans;

    inputFile.close();
    return 0;
}