#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
using namespace std;

struct VectorHash {
    size_t operator()(const vector<int>& vec) const {
        hash<int> hasher;
        size_t hash = 0;
        for (int i : vec) {
            hash ^= hasher(i) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

struct VectorEqual {
    bool operator()(const vector<int>& lhs, const vector<int>& rhs) const {
        return lhs == rhs;
    }
};

int count(string& s, int i, int j, int len, vector<int>& groups, unordered_map<vector<int>,int,VectorHash,VectorEqual> &dp) 
{
    if(j==groups.size() || (j==groups.size()-1 && groups[j]==len)) 
        return (s.length()==i || s.find("#", i)==string::npos);
    if(i==s.length()) 
        return 0;

    vector<int> key = {i,j,len};
    if(dp[key])
        return dp[key];

    int res = 0;
    if(len==groups[j] && s[i]!='#')
        res = count(s,i+1,j+1,0,groups,dp);
    else if(len==0) 
    {
        if(s[i]=='?') 
            res = count(s,i+1,j,1,groups,dp) + count(s,i+1,j,0,groups,dp);
        else if(s[i]=='#')
            res = count(s,i+1,j,1,groups,dp);
        else 
            res = count(s,i+1,j,0,groups,dp);
    } 
    else if(s[i]!='.')
        res = count(s,i+1,j,len+1,groups,dp);

    return dp[key] = res;
}

int main() 
{
    ifstream inputFile("text.txt");
    string line;

    long long ans = 0;
    while (getline(inputFile, line)) 
    {
        string pattern = line.substr(0,line.find(' '));
        istringstream ss(line.substr(line.find(' ')+1));
        vector<int> groups;
        string size;
        while (getline(ss, size, ','))
            groups.push_back(stoi(size));
        unordered_map<vector<int>, int, VectorHash, VectorEqual> dp;
        ans += count(pattern,0,0,0,groups,dp);
    }
    
    cout<<ans;
    inputFile.close();
    return 0;
}