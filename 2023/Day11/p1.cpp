#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() 
{
    ifstream inputFile("text.txt");
    string line;

    vector<vector<char>> space;

    while (getline(inputFile, line)) 
    {
        vector<char> temp(line.begin(), line.end());
        space.push_back(temp);
    }

    vector<int> er, ec;
    for(int i=0; i<space.size(); i++)
    {
        bool n = true;
        for(int j=0; j<space[0].size() && n; j++)
            n = space[i][j] != '#';
        if(n)
            er.push_back(i);
    }
    for(int j=0; j<space[0].size(); j++)
    {
        bool n = true;
        for(int i=0; i<space.size() && n; i++)
            n = space[i][j] != '#';
        if(n)
            ec.push_back(j);
    }

    vector<vector<int>> coords;
    for(int i=0; i<space.size(); i++)
    {
        for(int j=0; j<space[0].size(); j++)
        {
            if(space[i][j] == '#')
            {
                int rb = distance(er.begin(), upper_bound(er.begin(), er.end(), i));
                int rc = distance(ec.begin(), upper_bound(ec.begin(), ec.end(), j));
                coords.push_back({i+rb,j+rc});
            }
        }
    }

    int ans = 0;
    for(int i=0; i<coords.size(); i++)
    {
        for(int j=i+1; j<coords.size(); j++)
            ans += abs(coords[i][0]-coords[j][0]) + abs(coords[i][1]-coords[j][1]);
    }
    
    cout<<ans;
    inputFile.close();
    return 0;
}