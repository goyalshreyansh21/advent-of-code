#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

long long permutations(int xmax, int xmin, int mmax, int mmin, int amax, int amin, int smax, int smin, unordered_map<string,string> &m, string rule)
{
    if(rule=="A")
        return (long long)(xmax-xmin+1)*(mmax-mmin+1)*(amax-amin+1)*(smax-smin+1);
    if(rule=="R")
        return 0;
    
    int colon = rule.find(":"), comma = rule.find(",");
    if(colon==string::npos)
        return permutations(xmax,xmin,mmax,mmin,amax,amin,smax,smin,m,m[rule]);

    string con = rule.substr(0, colon);
    string t = rule.substr(colon + 1, comma - colon - 1);
    string f = rule.substr(comma + 1);

    long long ans = 0;
    int greater = con.find('<');
    if(greater != string::npos) 
    {
        char var = con.substr(0, greater)[0];
        int val = stoi(con.substr(greater+1));

        if((var=='x')&&(val>=xmin)&&(val<=xmax))
            ans += permutations(val-1,xmin,mmax,mmin,amax,amin,smax,smin,m,t) + permutations(xmax,val,mmax,mmin,amax,amin,smax,smin,m,f);
        if((var=='m')&&(val>=mmin)&&(val<=mmax))
            ans += permutations(xmax,xmin,val-1,mmin,amax,amin,smax,smin,m,t) + permutations(xmax,xmin,mmax,val,amax,amin,smax,smin,m,f);
        if((var=='a')&&(val>=amin)&&(val<=amax))
            ans += permutations(xmax,xmin,mmax,mmin,val-1,amin,smax,smin,m,t) + permutations(xmax,xmin,mmax,mmin,amax,val,smax,smin,m,f);
        if((var=='s')&&(val>=smin)&&(val<=smax))
            ans += permutations(xmax,xmin,mmax,mmin,amax,amin,val-1,smin,m,t) + permutations(xmax,xmin,mmax,mmin,amax,amin,smax,val,m,f);
    } 
    else 
    {
        int lesser = con.find('>');
        char var = con.substr(0, lesser)[0];
        int val = stoi(con.substr(lesser+1));
        
        if((var=='x')&&(val>=xmin)&&(val<=xmax))
            ans += permutations(xmax,val+1,mmax,mmin,amax,amin,smax,smin,m,t) + permutations(val,xmin,mmax,mmin,amax,amin,smax,smin,m,f);   
        if((var=='m')&&(val>=mmin)&&(val<=mmax))
            ans += permutations(xmax,xmin,mmax,val+1,amax,amin,smax,smin,m,t) + permutations(xmax,xmin,val,mmin,amax,amin,smax,smin,m,f);   
        if((var=='a')&&(val>=amin)&&(val<=amax))
            ans += permutations(xmax,xmin,mmax,mmin,amax,val+1,smax,smin,m,t) + permutations(xmax,xmin,mmax,mmin,val,amin,smax,smin,m,f);   
        if((var=='s')&&(val>=smin)&&(val<=smax))
            ans += permutations(xmax,xmin,mmax,mmin,amax,amin,smax,val+1,m,t) + permutations(xmax,xmin,mmax,mmin,amax,amin,val,smin,m,f);   
    }
    return ans;
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

    cout<<permutations(4000,1,4000,1,4000,1,4000,1,workflow,workflow["in"]);
    return 0;
}