#include <iostream>
#include <fstream>
using namespace std;

int main() 
{
    ifstream inputFile("text.txt");
    string line;
    long long ans = 0;

    while(getline(inputFile, line)) {
        int x1 = stoi(line.substr(line.find("X+")+2, line.find(',')-line.find('+')-1));
        int y1 = stoi(line.substr(line.find("Y+")+2));

        getline(inputFile, line);
        int x2 = stoi(line.substr(line.find("X+")+2, line.find(',')-line.find('+')-1));
        int y2 = stoi(line.substr(line.find("Y+")+2));

        getline(inputFile, line);
        long long x = 10000000000000 + stoi(line.substr(line.find("X=")+2, line.find(',')-line.find('+')-1));
        long long y = 10000000000000 + stoi(line.substr(line.find("Y=")+2));

        long long d = x1 * y2 - x2 * y1;
        long long n1 = x * y2 - y * x2;
        long long n2 = y * x1 - x * y1;

        if(n1%d == 0 && n2%d == 0)
            ans += 3 * n1/d + n2/d;

        getline(inputFile, line);
    }

    cout<<ans;

    inputFile.close();
    return 0;
}