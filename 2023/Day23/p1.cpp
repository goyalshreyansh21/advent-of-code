#include <iostream>
#include <fstream>
using namespace std;

void dfs(vector<string> &island, vector<vector<int>> &grid, int r, int c, int steps, vector<vector<int>> &visited)
{
    if(island[r][c]=='#' || visited[r][c]) 
        return;

    visited[r][c]++;
    grid[r][c] = max(grid[r][c], steps);

    if((c>0) && (island[r][c]=='.') || (island[r][c] == '<'))
        dfs(island,grid,r,c-1,steps+1,visited);
    if((c<island[0].length()-1) && (island[r][c]=='.') || (island[r][c]=='>'))
        dfs(island,grid,r,c+1,steps+1,visited);
    if((r>0) && (island[r][c]=='.') || (island[r][c]=='^'))
        dfs(island,grid,r-1,c,steps+1,visited);
    if((r<island.size()-1) && (island[r][c]=='.') || (island[r][c]=='v'))
        dfs(island,grid,r+1,c,steps+1,visited);

    visited[r][c]--;
}

int main() 
{
    ifstream inputFile("text.txt");
    string line;

    vector<string> island;

    while(getline(inputFile, line))
        island.push_back(line);
    
    int startx = 0, starty, endx = island.size()-1, endy;
    for(int j=0; j<island[0].size(); j++)
    {
        if(island[0][j]=='.')
            starty = j;
    }
    for(int j=0; j<island[endx].size(); j++)
    {
        if(island[endx][j]=='.')
            endy = j;
    }

    vector<vector<int>> visited(island.size(), vector<int>(island[0].length())), grid = visited;

    dfs(island,grid,startx,starty,0,visited);
    cout<<grid[endx][endy];
    inputFile.close();
    return 0;
}