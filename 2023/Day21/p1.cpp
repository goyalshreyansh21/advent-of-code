#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

int main() 
{
    ifstream inputFile("text.txt");
    string line;
    vector<string> plot;

    while(getline(inputFile, line))
        plot.push_back((line));

    queue<vector<int>> q;
    for(int i=0; i<plot.size() && q.empty(); i++)
    {
        for(int j=0; j<plot[0].size() && q.empty(); j++)
        {
            if(plot[i][j]=='S')
                q.push({i,j,64});
        }
    }

    vector<vector<int>> directions = {{0,1},{1,0},{-1,0},{0,-1}};
    vector<vector<int>> visited(plot.size(), vector<int>(plot[0].length()));
    while(!q.empty())
    {
        int x = q.front()[0], y = q.front()[1], rem = q.front()[2];
        visited[x][y] = 1;
        if(rem%2==0)
            plot[x][y]='O';
        
        for(vector<int> dir:directions)
        {
            int dx = x+dir[0], dy = y+dir[1];
            if(dx>=0 && dx<plot.size() && dy>=0 && dy<plot[0].length() && plot[dx][dy]=='.' && !visited[dx][dy] && rem>0)
            {
                visited[dx][dy] = 1;
                q.push({dx,dy,rem-1});

            }
        }
        q.pop();
    }

    int ans = 0;
    for(int i=0; i<plot.size(); i++)
    {
        for(char c:plot[i])
            ans += c=='O';
    }
    cout<<ans;
    inputFile.close();
    return 0;
}