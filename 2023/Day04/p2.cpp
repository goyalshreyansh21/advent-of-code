#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
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
    int lines = 0;
    while(getline(inputFile, line))
        lines++;
    inputFile.close();

    long long ans = 0;
    vector<int> v(lines+1,1);
    int i = 1;

    ifstream inputFile1("text.txt");
    while(getline(inputFile1, line)) 
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

        for(int k=i+1; k<i+1+match; k++)
            v[k] += v[i];

        ans += v[i];
        i++;
    }
    
    cout<<ans;
    inputFile1.close();
    return 0;
}