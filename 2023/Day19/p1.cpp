#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

string solve(unordered_map<char,int> &p, unordered_map<string,string> &m, string rule)
{
    if(rule=="R" || rule=="A")
        return rule;

    int colon = rule.find(":"), comma = rule.find(",");
    if(colon==string::npos)
        return solve(p,m,m[rule]);

    string con = rule.substr(0, colon);
    string t = rule.substr(colon + 1, comma - colon - 1);
    string f = rule.substr(comma + 1);

    int greater = con.find('<');
    if(greater != string::npos) 
    {
        char var = con.substr(0, greater)[0];
        int value = stoi(con.substr(greater+1));
        con = p[var]<value ? t : f;
    } 
    else 
    {
        int lesser = con.find('>');
        char var = con.substr(0, lesser)[0];
        int value = stoi(con.substr(lesser+1));
        con = p[var]>value ? t : f;
    }

    return solve(p,m,con);
}

int main() 
{
    ifstream inputFile("text.txt");
    string line;

    unordered_map<string,string> workflow;
    workflow["A"] = "A";
    workflow["R"] = "R";

    while(getline(inputFile, line))
    {
        if(line.empty())
            break;
        string name = line.substr(0, line.find('{'));
        string rule = line.substr(line.find('{')+1, line.find('}')-line.find('{')-1);
        workflow[name] = rule;
    }

    int ans = 0;
    while(getline(inputFile, line))
    {
        int xPos = line.find('x')+2, mPos = line.find('m')+2, aPos = line.find('a')+2, sPos = line.find('s')+2;

        unordered_map<char,int> part;
        part['x'] = stoi(line.substr(xPos, mPos-xPos-3));
        part['m'] = stoi(line.substr(mPos, aPos-mPos-3));
        part['a'] = stoi(line.substr(aPos, sPos-aPos-3));
        part['s'] = stoi(line.substr(sPos));

        if(solve(part,workflow,workflow["in"])=="A")
            ans += part['x']+part['m']+part['a']+part['s'];
    }

    cout<<ans;
    inputFile.close();
    return 0;
}