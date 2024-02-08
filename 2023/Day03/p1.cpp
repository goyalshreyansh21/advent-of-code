#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

bool ispart(vector<vector<char>> &v, int row, int start, int end)
{
    queue<vector<int>> q;
    q.push({row,start-1});
    q.push({row,end+1});
    for(int i=start-1; i<=end+1; i++)
    {
        q.push({row-1,i});
        q.push({row+1,i});
    }

    while(!q.empty())
    {
        int x = q.front()[0], y = q.front()[1];
        q.pop();
        if((x<0)||(x>=v.size())||(y<0)||(y>=v[0].size()))
            continue;

        if(v[x][y]!='.')
            return true;
    }
    return false;
}

int convert(vector<vector<char>> &v, int row, int start, int end)
{
    int num = 0;
    for(int i=start; i<=end; i++)
        num = num*10 + v[row][i]-'0';
    return num;
}

int main() 
{
    ifstream inputFile("text.txt");

    string line;
    long long ans = 0;
    
    vector<vector<char>> v;
    while (getline(inputFile, line)) 
    {
        vector<char> l(line.begin(), line.end());
        v.push_back(l);
    }
    
    for(int i=0; i<v.size(); i++)
    {
        for(int j=0; j<v[0].size(); j++)
        {
            if(isdigit(v[i][j]))
            {
                int endj = j;
                while((endj+1<v[0].size())&&(isdigit(v[i][endj+1])))
                    endj++;

                if(ispart(v,i,j,endj))
                {
                    int add = convert(v,i,j,endj);
                    ans += add;
                }

                j = endj;
            }
        }
    }
    cout<<ans;
    inputFile.close();
    return 0;
}