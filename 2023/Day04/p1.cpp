#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
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
    if(temp!="")
        v.push_back(temp);
    return v;
}

int main() 
{
    ifstream inputFile("text.txt");

    string line;
    long long ans = 0;

    while (getline(inputFile, line)) 
    {
        vector<string> card = ssplit(line,':');
        vector<string> numbers = ssplit(card[1],'|');
        vector<string> win = ssplit(numbers[0],' ');
        vector<string> num = ssplit(numbers[1],' ');
        
        unordered_set<int> set;
        
        for(string s:win)
            set.insert(stoi(s));

        int match = 0;
        for(string s:num)
        {
            if(set.find(stoi(s))!=set.end())
                match++;
        }
        ans += match ? (int)pow(2,match-1) : 0;
    }
    
    cout<<ans;
    inputFile.close();
    return 0;
}