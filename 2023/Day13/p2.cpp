#include <iostream>
#include <fstream>
using namespace std;

int findsplit(vector<string> pattern)
{
    for(int i=1; i<=pattern.size()-1; i++)
    {
        int diff = 0, top = i-1, bottom = i;
        while(top>=0 && bottom<pattern.size())
        {
            for(int j=0; j<pattern[0].size(); j++)
            {
                if(pattern[top][j]!=pattern[bottom][j])
                    diff++;
            }
            top--;
            bottom++;
        }
        if(diff==1)
            return 100*i;
    }

    for(int i=1; i<pattern[0].size(); i++)
    {
        int diff = 0, left = i-1, right = i;
        while(left>=0 && right<pattern[0].size())
        {
            for(int j=0; j<pattern.size(); j++)
            {
                if(pattern[j][left]!=pattern[j][right])
                    diff++;
            }
            left--;
            right++;
        }
        if(diff==1)
            return i;   
    }
    return -1;
}

int main() 
{
    ifstream inputFile("text.txt");
    string line;
    vector<vector<string>> patterns;
    vector<string> temp;

    while(getline(inputFile, line)) 
    {
        if(line.empty())
        {
            patterns.push_back(temp);
            temp.clear();
        }
        else
            temp.push_back(line);
    }
    patterns.push_back(temp);

    int ans = 0;
    for(vector<string> pattern:patterns)
        ans+= findsplit(pattern);

    cout<<ans;
    inputFile.close();
    return 0;
}