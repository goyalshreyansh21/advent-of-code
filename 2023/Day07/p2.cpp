#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

class Hand
{
public:
    vector<int> cards;
    int bid;
    int type;
    Hand(vector<int> v, int x, int y)
    {
        cards = v;
        bid = x;
        type = y;
    }
};

static bool cmp(Hand &h1, Hand &h2)
{
    if(h1.type != h2.type)
        return h1.type > h2.type;
    
    for(int i=0; i<5; i++)
    {
        if(h1.cards[i] != h2.cards[i])
            return h1.cards[i] > h2.cards[i];
    } 
    return h1.bid > h2.bid;
}

int typecard(string s)
{
    vector<int> v(12);
    int j=0;
    for(char c:s)
    {
        if(c=='A')
            v[0]++;
        else if(c=='K')
            v[11]++;
        else if(c=='Q')
            v[10]++;
        else if(c=='J')
            j++;
        else if(c=='T')
            v[9]++;
        else
            v[c-'1']++;
    }
    sort(v.begin(),v.end(),greater<int>());
    
    if(v[0]+j==5)
        return 7;
    if(v[0]+j==4)
        return 6;
    if(v[0]+j==3)
        return v[1]==2 ? 5 : 4;
    if(v[0]+j==2)
        return v[1]==2 ? 3 : 2;
    return 1;
}

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
    if(temp!="")
        v.push_back(temp);
    return v;
}

int main() 
{
    ifstream inputFile("text.txt");

    string line;

    vector<Hand> allhands;
    while (getline(inputFile, line)) 
    {
        vector<string> hand = ssplit(line,' ');
        vector<int> v;

        for(char c:hand[0])
        {
            if(c=='A')
                v.push_back(13);
            else if(c=='K')
                v.push_back(12);
            else if(c=='Q')
                v.push_back(11);
            else if(c=='T')
                v.push_back(10);
            else if(c=='J')
                v.push_back(1);
            else 
                v.push_back(c-'0');
        }
        allhands.push_back(Hand(v,stoi(hand[1]),typecard(hand[0])));
    }
    
    sort(allhands.begin(), allhands.end(), cmp);

    long long ans = 0;
    int i = allhands.size();

    for(Hand h:allhands)
    {
        ans += (long long)h.bid*i;
        i--;
    }

    cout<<ans;
    inputFile.close();
    return 0;
}