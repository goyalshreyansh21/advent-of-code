#include <iostream>
#include <fstream>
using namespace std;

int main() 
{
    ifstream inputFile("text.txt");
    string pattern;

    long long ans = 0;
    while(getline(inputFile, pattern, ','))
    {
        int h = 0;
        for(char c:pattern)
            h = (h+c)*17 % 256;
        ans += h;
    }

    cout<<ans;
    inputFile.close();
    return 0;
}