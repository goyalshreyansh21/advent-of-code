#include <iostream>
#include <fstream>
#include <string>
#include <cctype>  
using namespace std;

int main() 
{
    ifstream inputFile("text.txt");

    string line;
    long long ans = 0;
    while (getline(inputFile, line)) 
    {
        int f = -1, l = -1;
        for(char c:line)
        {
            if(isdigit(c))
            {
                if(f==-1)
                    f = c-'0';
                l = c-'0';
            }
        }
        ans += f*10+l;
    }
    cout<<ans;
    
    inputFile.close();
    return 0;
}
