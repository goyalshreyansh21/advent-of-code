#include <iostream>
#include <fstream>
using namespace std;

int findsplit(vector<string> pattern)
{
    for(int i=1; i<=pattern.size()-1; i++)
    {
        bool mirr = true;
        int top = i-1, bottom = i;
        while(top>=0 && bottom<pattern.size() && mirr)
        {
            if(pattern[top--]!=pattern[bottom++])
                mirr = false;
        }
        if(mirr)
            return 100*i;
    }

    for(int i=1; i<pattern[0].size(); i++)
    {
        bool mirr = true;
        int left = i-1, right = i;
        while(left>=0 && right<pattern[0].size() && mirr)
        {
            for(int j=0; j<pattern.size(); j++)
            {
                if(pattern[j][left]!=pattern[j][right])
                    mirr = false;
            }
            left--;
            right++;
        }
        if(mirr)
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