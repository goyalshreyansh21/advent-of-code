#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
using namespace std;

int main() 
{
    ifstream inputFile("text.txt");
    string line;

    int n = 101, m = 103;
    regex pattern(R"(p=(-?[0-9]+),(-?[0-9]+) v=(-?[0-9]+),(-?[0-9]+))");
    smatch match;

    vector<int> q(4);
    while(getline(inputFile, line)) {
        regex_search(line, match, pattern);
        int x = stoi(match[1].str());
        int y = stoi(match[2].str());
        int vx = stoi(match[3].str());
        int vy = stoi(match[4].str());

        x = (x+ ((vx<0 ? n : 0) + vx)*100)%n;
        y = (y+ ((vy<0 ? m : 0) + vy)*100)%m;

        q[(x>n/2) * 2 + (y>n/2)]++;
    }

    int ans = 1;
    for(int& i:q)
        ans *= i;
    cout<<ans;

    inputFile.close();
    return 0;
}