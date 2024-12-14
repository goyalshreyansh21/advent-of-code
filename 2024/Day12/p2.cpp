#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

bool isSame(vector<vector<int>>& v, int i, int j, int x, int y) {
    if(x<0 || x==v.size() || y<0 || y==v[0].size())
        return false;
    return v[i][j] == v[x][y];
}

bool isDifferent(vector<vector<int>>& v, int i, int j, int x, int y) {
    if(x<0 || x==v.size() || y<0 || y==v[0].size())
        return true;
    return v[i][j] != v[x][y];
}

int area(vector<vector<int>>& v, int n) {
    int c = 0;
    for(vector<int>& f:v) 
        for(int& i:f) 
            if(i == n)
                c++;
    return c;
}

int sides(vector<vector<int>>& v, int n) {
    int c = 0;
    for(int i=0; i<v.size(); i++) {
        for(int j=0; j<v[0].size(); j++) {
            if(v[i][j] == n) {
                if(isDifferent(v,i,j,i-1,j) && isDifferent(v,i,j,i,j-1))
                    c++;
                if(isDifferent(v,i,j,i-1,j) && isDifferent(v,i,j,i,j+1))
                    c++;
                if(isDifferent(v,i,j,i+1,j) && isDifferent(v,i,j,i,j-1))
                    c++;
                if(isDifferent(v,i,j,i+1,j) && isDifferent(v,i,j,i,j+1))
                    c++;
                
                if(isSame(v,i,j,i-1,j) && isDifferent(v,i,j,i-1,j-1) && isSame(v,i,j,i,j-1))
                    c++;
                if(isSame(v,i,j,i-1,j) && isDifferent(v,i,j,i-1,j+1) && isSame(v,i,j,i,j+1))
                    c++;
                if(isSame(v,i,j,i+1,j) && isDifferent(v,i,j,i+1,j-1) && isSame(v,i,j,i,j-1))
                    c++;
                if(isSame(v,i,j,i+1,j) && isDifferent(v,i,j,i+1,j+1) && isSame(v,i,j,i,j+1))
                    c++;
            }
        }
    }
    return c;
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
                ans += area(farmtype, f) * sides(farmtype, f);
                f++;
            }
        }
    }

    cout << ans;

    inputFile.close();
    return 0;
}