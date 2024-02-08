#include <iostream>
#include <fstream>
#include <string>
using namespace std;

vector<string> ssplit(string &s, char c)
{
    vector<string> v;
    string temp;
    for(char i:s)
    {
        if((i==c)&&(temp!=""))
        {
            v.push_back(temp);
            temp = "";
        }
        else
            temp += i;
    }
    v.push_back(temp);
    return v;
}

int main() 
{
    ifstream inputFile("text.txt");

    string line;
    long long ans = 0;
    int i = 1;
    int r = 12, g = 13, b = 14;
    while (getline(inputFile, line)) 
    {
        int maxr = 0, maxg = 0, maxb = 0;
        vector<string> game = ssplit(line,':');
        vector<string> round = ssplit(game[1],';');

        for(string s:round)
        {
            int tempr = 0, tempg = 0, tempb = 0;
            vector<string> item = ssplit(s,',');
            for(string k:item)
            {
                vector<string> v = ssplit(k,' ');
                
                if(v[1]=="blue")
                    tempb += stoi(v[0]); 
                if(v[1]=="red")
                    tempr += stoi(v[0]); 
                if(v[1]=="green")
                    tempg += stoi(v[0]); 
            }
            maxr = max(maxr, tempr);
            maxg = max(maxg, tempg);
            maxb = max(maxb, tempb);
        }
        if((maxr<=r)&&(maxg<=g)&&(maxb<=b))
            ans += i;
        i++;
    }
    cout<<ans;
    
    inputFile.close();
    return 0;
}
