#include <iostream>
#include <fstream>
using namespace std;

void fix(vector<string> &rocks, int j, int start, int end)
{
    int r = 0;
    for(int i=start; i<end; i++)
        r += rocks[i][j]=='O';
    
    for(int i=start; i<end; i++)
        rocks[i][j] = r-->0 ? 'O' : '.';
}

int main() 
{
    ifstream inputFile("text.txt");
    string line;
    vector<string> rocks;

    while(getline(inputFile, line)) 
        rocks.push_back(line);

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
            fix(rocks,j,hp[k]+1,hp[k+1]);
    }

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