#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
using namespace std;

int index(unordered_map<string,int> &m, string s)
{
    if(m.find(s)!=m.end())
        return m[s];
    return m[s] = m.size();
}

int main() 
{
    ifstream inputFile("text.txt");
    string line;
    unordered_map<string,int> m;
    vector<vector<int>> adj(1528, vector<int>(1528));

    while(getline(inputFile, line))
    {
        string s;
        istringstream iss(line);
        getline(iss,s,':');
        int i = index(m,s);
        while(getline(iss,s,' '))
        {
            if(s.empty())
                continue;
            adj[i][index(m,s)] = 1;
            adj[index(m,s)][i] = 1;
        }
    }

    pair<int,vector<int>> best = {INT_MAX, {}};
    int n = adj.size();
    vector<vector<int>> co(n);

    for(int i=0; i<adj.size(); i++)
        co[i] = {i};

    for(int ph=1; ph<adj.size(); ph++) 
    {
        vector<int> w = adj[0];
        int s = 0, t = 0;
        for(int it=0; it<adj.size()-ph; it++) 
        {
            w[t] = INT_MIN;
            s = t;
            t = max_element(w.begin(), w.end()) - w.begin();
            for(int i=0; i<adj.size(); i++) 
                w[i] += adj[t][i];
        }

        best = min(best, {w[t]-adj[t][t], co[t]});
        co[s].insert(co[s].end(), co[t].begin(), co[t].end());
        for(int i=0; i<adj.size(); i++)
            adj[s][i] += adj[t][i];
        for(int i=0; i<adj.size(); i++)
            adj[i][s] = adj[s][i];
        adj[0][t] = INT_MIN;
    }

    int ans = best.second.size() * (m.size() -best.second.size());
    cout<<ans;
    inputFile.close();
    return 0;
}