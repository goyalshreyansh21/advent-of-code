#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
using namespace std;

pair<char,int> split(string s)
{
    pair<char,int> p;
    p.first = s[0];
    int i=2;
    for(; s[i]!=' '; i++);
    p.second = stoi(s.substr(2,i));
    return p;
}

int main() 
{
    ifstream inputFile("text.txt");
    string line;

    unordered_map<char, vector<int>> m;
    m['R'] = {0,1};
    m['L'] = {0,-1};
    m['U'] = {-1,0};
    m['D'] = {1,0};

    int cx = 0, cy = 0, px = -1, py = -1;
    int area = 0, perimeter = 0;

    while(getline(inputFile, line))
    {
        pair<char,int> p = split(line);
        px = cx;
        py = cy;
        cx += m[p.first][0]*p.second;
        cy += m[p.first][1]*p.second;
        area += px*cy - cx*py;
        perimeter += abs(px-cx + py-cy);
    }

    cout<<abs(area)/2+abs(perimeter)/2+1;
    inputFile.close();
    return 0;
}