#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    ifstream inputFile("text.txt");
    string line;

    vector<vector<int>> secrets;

    while(getline(inputFile, line)) {
        long long n = stoll(line);
        vector<int> temp(1,n);
        for(int i=0; i<2000; i++) {
            n = ((n*64) ^ n) % 16777216;
            n = (n/32 ^ n) % 16777216;
            n = ((n*2048) ^ n) % 16777216;
            temp.push_back(n%10);
        }
        secrets.push_back(temp);
    } 

    unordered_map<string,int> m;
    for(vector<int>& v:secrets) {
        unordered_map<string,int> temp;
        for(int i=4; i<v.size(); i++) {
            string s = to_string(v[i-3]-v[i-4]) + to_string(v[i-2]-v[i-3]) + to_string(v[i-1]-v[i-2]) + to_string(v[i]-v[i-1]);
            
            if(temp.find(s) == temp.end())
                temp[s] = v[i];
        }
        for(pair<const string, int>&p:temp) 
            m[p.first] += p.second;
    }

    int ans = 0;  
    for(pair<const string, int>&p:m) 
        ans = max(ans,p.second);

    cout << ans;

    inputFile.close();
    return 0;
}