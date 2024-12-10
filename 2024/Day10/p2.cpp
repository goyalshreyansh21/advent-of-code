#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int paths(vector<vector<int>>& dp, vector<vector<int>>& grid, int x, int y, int cur) {
    if(cur == 9)
        return dp[x][y] = 1;
    if(dp[x][y] != -1)
        return dp[x][y];
    
    int temp = 0;

    if(x > 0 && grid[x-1][y] == cur+1)
        temp += paths(dp, grid, x-1, y, cur+1);
    if(x < grid.size()-1 && grid[x+1][y] == cur+1)
        temp += paths(dp, grid, x+1, y, cur+1);
    if(y > 0 && grid[x][y-1] == cur+1)
        temp += paths(dp, grid, x, y-1, cur+1);
    if(y < grid[0].size()-1 && grid[x][y+1] == cur+1)
        temp += paths(dp, grid, x, y+1, cur+1);

    return dp[x][y] = temp;
}

int main() 
{
    ifstream inputFile("text.txt");
    string line;
    vector<vector<int>> grid;

    while(getline(inputFile, line)) {
        vector<int> row;
        for(char& c:line)
            row.push_back(c-'0');
        grid.push_back(row);
    }

    int ans = 0;
    vector<vector<int>> dp(grid.size(), vector<int>(grid[0].size(),-1));
    for(int i=0; i<grid.size(); i++) 
        for(int j=0; j<grid.size(); j++) 
            if(grid[i][j] == 0)
                ans += paths(dp, grid, i, j, 0);

    cout<<ans;

    inputFile.close();
    return 0;
}