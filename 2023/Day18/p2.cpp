#include <iostream>
#include <fstream>
using namespace std;

int main() 
{
    ifstream inputFile("text.txt");
    string line;
    
    vector<vector<int>> dir = {{0,1},{1,0},{0,-1},{-1,0}};

    long long cx = 0, cy = 0, px = -1, py = -1;
    long long area = 0, perimeter = 0;

    while(getline(inputFile, line))
    {
        string word = line.substr(line.find('#')+1,6);
        int i = word[5]-'0', count = stoi(word.substr(0,5), nullptr, 16);

        px = cx;
        py = cy;
        cx += dir[i][0]*count;
        cy += dir[i][1]*count;
        area += px*cy - cx*py;
        perimeter += abs(px-cx + py-cy);
    }

    cout<<abs(area)/2+abs(perimeter)/2+1;
    inputFile.close();
    return 0;
}