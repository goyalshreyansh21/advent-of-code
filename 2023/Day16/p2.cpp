#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

void bfs(int r, int c, vector<string> &space, vector<vector<int>> &visited, char dir, unordered_map<char,vector<int>> &m, unordered_set<string> &s)
{
    if(s.find(to_string(r)+'-'+to_string(c)+'-'+dir)!=s.end())
        return;
    s.insert(to_string(r)+'-'+to_string(c)+'-'+dir);
    if(r<0 || r>=space.size() || c<0 || c>=space[0].length())
        return;

    visited[r][c]++;
    if((space[r][c]=='.')||(space[r][c]=='|' && (dir=='u' || dir=='d'))||(space[r][c]=='-' && (dir=='r' || dir=='l')))
    {
        int dr = r+m[dir][0], dc = c+m[dir][1];
        bfs(dr,dc,space,visited,dir,m,s);
    }
    else if(space[r][c] == '\\' || space[r][c] == '/')
    {
        char newd;
        if(dir=='r')
            newd = space[r][c] == '\\' ? 'd' : 'u';
        else if(dir=='l')
            newd = space[r][c] == '\\' ? 'u' : 'd';
        if(dir=='d')
            newd = space[r][c] == '\\' ? 'r' : 'l';
        if(dir=='u')
            newd = space[r][c] == '\\' ? 'l' : 'r';

        int dr = r+m[newd][0], dc = c+m[newd][1];
        bfs(dr,dc,space,visited,newd,m,s);
    }
    else
    {
        if(dir=='r' || dir=='l')
        {
            bfs(r-1,c,space,visited,'u',m,s);
            bfs(r+1,c,space,visited,'d',m,s);
        }
        else
        {
            bfs(r,c-1,space,visited,'l',m,s);
            bfs(r,c+1,space,visited,'r',m,s);
        }
    }
}

int helper(int r, int c, char dir, vector<string> &space, unordered_map<char,vector<int>> &m)
{
    vector<vector<int>> visited(space.size(), vector<int>(space[0].size()));
    unordered_set<string> s;
    bfs(r,c,space,visited,dir,m,s);

    int energised = 0;
    for(vector<int> v:visited)
    {
        for(int i:v)
            energised += i>0;
    }
    return energised;
}

int main() 
{
    ifstream inputFile("text.txt");
    string line;

    vector<string> space;
    while(getline(inputFile, line))
        space.push_back(line);

    unordered_map<char,vector<int>> m;
    m['r'] = {0,1};
    m['l'] = {0,-1};
    m['u'] = {-1,0};
    m['d'] = {1,0};

    
    int ans = 0;
    for(int i=0; i<space.size(); i++)
        ans = max({ans, helper(i,0,'r',space,m), helper(i,space[0].size()-1,'l',space,m)});
    for(int j=0; j<space[0].size(); j++)
        ans = max({ans, helper(0,j,'d',space,m), helper(space.size()-1,j,'u',space,m)});
    
    cout<<ans;
    inputFile.close();
    return 0;
}