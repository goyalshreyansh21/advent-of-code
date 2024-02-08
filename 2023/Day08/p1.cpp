#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
using namespace std;

int main() 
{
    ifstream inputFile("text.txt");
    string dir, line;
    getline(inputFile,dir);
    getline(inputFile,line);
    unordered_map<string,vector<string>> m;

    while (getline(inputFile, line)) 
    {
        istringstream iss(line);
        string s, l, r;

        iss >> s;
        iss.ignore(line.length(), '(');

        getline(iss, l, ',');
        iss.ignore(line.length(), ' ');
        getline(iss, r, ')');
        m[s] = {l,r};
    }

    int ans = 0, i = 0;
    string curr = "AAA";
    while(curr!="ZZZ")
    {
        curr = m[curr][dir[i] == 'R'];
        i = (i+1)%dir.length();
        ans++;
    }
    
    cout<<ans;
    inputFile.close();
    return 0;
}