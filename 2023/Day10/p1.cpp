#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

int main() 
{
    ifstream inputFile("text.txt");
    string line;
    int ans = 0;
    vector<vector<char>> maze;

    unordered_map<char,vector<vector<int>>> map;
    map['|'] = {{-1,0},{1,0}};
    map['|'] = {{-1,0},{1,0}};
    map['-'] = {{0,1},{0,-1}};
    map['L'] = {{-1,0},{0,1}};
    map['J'] = {{-1,0},{0,-1}};
    map['F'] = {{0,1},{1,0}};
    map['7'] = {{1,0},{0,-1}};
    map['S'] = map['|'];


    while (getline(inputFile, line)) 
    {
        vector<char> temp(line.begin(), line.end());
        maze.push_back(temp);
    }
    
    vector<int> startpos, currpos;
    vector<int> prevpos {-1,-1};
    for(int i=0; i<maze.size(); i++)
    {
        for(int j=0; j<maze[0].size(); j++)
        {
            if(maze[i][j]=='S')
            {
                currpos = {i,j};
                startpos = {i,j};
                break;
            }
        }
    }

    do
    {
        int x = currpos[0], y = currpos[1];
        char c = maze[x][y];
        if(prevpos != vector<int> {x+map[c][0][0], y+map[c][0][1]})
        {
            prevpos = currpos;
            currpos = {x+map[c][0][0], y+map[c][0][1]};
        }
        else
        {
            prevpos = currpos;
            currpos = {x+map[c][1][0], y+map[c][1][1]};
        }
        ans++;
    }
    while(currpos!=startpos);

    cout<<ans/2;
    inputFile.close();
    return 0;
}