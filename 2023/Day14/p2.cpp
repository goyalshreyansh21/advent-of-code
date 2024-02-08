#include <iostream>
#include <fstream>
using namespace std;

void tiltnorth(vector<string> &rocks, int j, int start, int end)
{
    int r = 0;
    for(int i=start; i<end; i++)
        r += rocks[i][j]=='O';
    
    for(int i=start; i<end; i++)
        rocks[i][j] = r-->0 ? 'O' : '.';
}

void tiltwest(vector<string> &rocks, int i, int start, int end)
{
    int r = 0;
    for(int j=start; j<end; j++)
        r += rocks[i][j]=='O';
    
    for(int j=start; j<end; j++)
        rocks[i][j] = r-->0 ? 'O' : '.';
}

void tiltsouth(vector<string> &rocks, int j, int start, int end)
{
    int r = 0;
    for(int i=start; i<end; i++)
        r += rocks[i][j]=='.';
    
    for(int i=start; i<end; i++)
        rocks[i][j] = r-->0 ? '.' : 'O';
}

void tilteast(vector<string> &rocks, int i, int start, int end)
{
    int r = 0;
    for(int j=start; j<end; j++)
        r += rocks[i][j]=='.';
    
    for(int j=start; j<end; j++)
        rocks[i][j] = r-->0 ? '.' : 'O';
}

int seen(vector<vector<string>> &dp, vector<string> &rocks)
{
    for(int i=0; i<dp.size(); i++) 
    {
        if(dp[i]==rocks)
            return i;
    }
    return -1;
}

int main() 
{
    ifstream inputFile("text.txt");
    string line;
    vector<string> rocks;

    while(getline(inputFile, line)) 
        rocks.push_back(line);

    vector<vector<string>> dp;
    int first = -1, second = -1;
    for(int n=0; n<1000000000; n++)
    {
        int idx = seen(dp,rocks);
        if(idx!=-1)
        {
            first = idx;
            second = n;
            break;
        }
        else
            dp.push_back(rocks);

        for(int j=0; j<rocks[0].length(); j++)
        {
            vector<int> hp;
            hp.push_back(-1);
            for(int i=0; i<rocks.size(); i++)
            {
                if(rocks[i][j]=='#')
                    hp.push_back(i);
            }
            hp.push_back(rocks.size());

            for(int k=0; k<hp.size()-1; k++)
                tiltnorth(rocks,j,hp[k]+1,hp[k+1]);
        }

        for(int i=0; i<rocks.size(); i++)
        {
            vector<int> hp;
            hp.push_back(-1);
            for(int j=0; j<rocks[0].size(); j++)
            {
                if(rocks[i][j]=='#')
                    hp.push_back(j);
            }
            hp.push_back(rocks[0].size());

            for(int k=0; k<hp.size()-1; k++)
                tiltwest(rocks,i,hp[k]+1,hp[k+1]);
        }

        for(int j=0; j<rocks[0].length(); j++)
        {
            vector<int> hp;
            hp.push_back(-1);
            for(int i=0; i<rocks.size(); i++)
            {
                if(rocks[i][j]=='#')
                    hp.push_back(i);
            }
            hp.push_back(rocks.size());

            for(int k=0; k<hp.size()-1; k++)
                tiltsouth(rocks,j,hp[k]+1,hp[k+1]);
        }

        for(int i=0; i<rocks.size(); i++)
        {
            vector<int> hp;
            hp.push_back(-1);
            for(int j=0; j<rocks[0].size(); j++)
            {
                if(rocks[i][j]=='#')
                    hp.push_back(j);
            }
            hp.push_back(rocks[0].size());

            for(int k=0; k<hp.size()-1; k++)
                tilteast(rocks,i,hp[k]+1,hp[k+1]);
        }

    }

    int idx = (1000000000-first) % (second - first) + first;
    rocks = dp[idx];
    int ans = 0;
    for(int i=0; i<rocks.size(); i++)
    {
        int rock = 0; 
        for(char c:rocks[i])
            rock += c=='O';
        ans += (rocks.size()-i)*rock;
    }    

    cout<<ans;
    inputFile.close();
    return 0;
}