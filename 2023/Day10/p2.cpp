#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
using namespace std;

int main() 
{
    ifstream inputFile("text.txt");

    unordered_map<char,vector<vector<int>>> map;
    map['|'] = {{-1,0},{1,0}};
    map['|'] = {{-1,0},{1,0}};
    map['-'] = {{0,1},{0,-1}};
    map['L'] = {{-1,0},{0,1}};
    map['J'] = {{-1,0},{0,-1}};
    map['F'] = {{0,1},{1,0}};
    map['7'] = {{1,0},{0,-1}};
    map['S'] = map['|'];

    vector<vector<char>> maze;
    string line;
    while (getline(inputFile, line)) 
    {
        vector<char> temp(line.begin(), line.end());
        maze.push_back(temp);
    }
    
    vector<int> startpos;
    for(int i=0; i<maze.size(); i++)
    {
        for(int j=0; j<maze[0].size(); j++)
        {
            if(maze[i][j]=='S')
            {
                startpos = {i,j};
                break;
            }
        }
    }

    vector<vector<int>> path;
    path.push_back(startpos);
    do
    {
        vector<int> currpos = path.back();
        vector<int> prevpos = (path.size()==1) ? vector<int> {-1,-1} : path[path.size()-2];
        int x = currpos[0], y = currpos[1];
        char c = maze[x][y];
        if(prevpos != vector<int> {x+map[c][0][0], y+map[c][0][1]})
            path.push_back({x+map[c][0][0], y+map[c][0][1]});
        else
            path.push_back({x+map[c][1][0], y+map[c][1][1]});
        if(path.back()==vector<int> {4,19})
            cout<<"f";
    }
    while(path.back()!=startpos);

    int ans = 0;
    for(int i=0; i<maze.size(); i++) 
    {
        int parity = 0;
        char enterPipe;
        for(int j=0; j<maze[i].size(); j++) 
        {
            if(find(path.begin(), path.end(), vector<int> {i,j}) == path.end()) 
                ans += parity%2;

            else 
            {
                path.erase(find(path.begin(), path.end(), vector<int> {i,j}));
                switch(maze[i][j]) 
                {
                    case '|':
                        parity++;
                        break;
                    case 'F':
                    case 'L':
                        enterPipe = maze[i][j];
                        break;
                    case '7':
                        parity += (enterPipe=='L');
                        break;
                    case 'J':
                        parity += (enterPipe=='F');
                }
            }
        }
    }

    cout<<ans;
    inputFile.close();
    return 0;
}