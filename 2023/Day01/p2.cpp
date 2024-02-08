#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>    
using namespace std;

static inline void ReplaceAll(string &str, const string& from, const string& to)
{    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

int main() 
{
    ifstream inputFile("text.txt");

    string line;
    long long ans = 0;
    while (getline(inputFile, line)) 
    {
        ReplaceAll(line, string("one"), "one1one");    
        ReplaceAll(line, string("two"), "two2two");    
        ReplaceAll(line, string("three"), "three3three");    
        ReplaceAll(line, string("four"), "four4four");    
        ReplaceAll(line, string("five"), "five5five");    
        ReplaceAll(line, string("six"), "six6six");    
        ReplaceAll(line, string("seven"), "seven7seven");    
        ReplaceAll(line, string("eight"), "eight8eight");    
        ReplaceAll(line, string("nine"), "nine9nine");    
   
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
