#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
using namespace std;

int steps(string s, unordered_map<string,vector<string>> &m, string dir) 
{
    int ans = 0, i = 0;
    string curr = s;
    while(curr[2]!='Z')
    {
        curr = m[curr][dir[i] == 'R'];
        i = (i+1)%dir.length();
        ans++;
    }
    return ans;
}

long long gcd(long long num1, long long num2)
{
    if (num2 == 0)
        return num1;
    return gcd(num2, num1 % num2);
}
 
long long lcm(vector<int> arr)
{
    long long lcm = arr[0];
    for(int i=1; i<arr.size(); i++) 
    {
        long long num1 = lcm;
        long long num2 = arr[i];
        long long gcd_val = gcd(num1, num2);
        lcm = (lcm * arr[i]) / gcd_val;
    }
    return lcm;
}

int main() 
{
    ifstream inputFile("text.txt");
    string dir, line;
    getline(inputFile,dir);
    getline(inputFile,line);
    unordered_map<string,vector<string>> m;
    vector<string> curr;
    vector<int> n;

    while (getline(inputFile, line)) 
    {
        istringstream iss(line);
        string s, l, r;

        iss >> s;
        iss.ignore(line.length(), '(');

        getline(iss, l, ',');
        iss.ignore(line.length(), ' ');
        getline(iss, r, ')');
        m[s] = {l,r};
        if(s[2]=='A')
            curr.push_back(s);
    }
    
    for(string s:curr)
        n.push_back(steps(s,m,dir));

    cout<<lcm(n);

    inputFile.close();
    return 0;
}