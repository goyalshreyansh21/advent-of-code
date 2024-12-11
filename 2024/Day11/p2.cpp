#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
using namespace std;

int main() 
{
    ifstream inputFile("text.txt");
    string line;

    getline(inputFile, line);
    stringstream ss(line);
    int n;

    unordered_map<long long, long long> freq;
    while(ss >> n)
        freq[n]++;
    
    for(int i=0; i<75; i++) {
        unordered_map<long long, long long> temp;
        for(auto& it:freq) {
            if(it.first == 0)
                temp[1] += it.second;
            else if(to_string(it.first).length() % 2 == 0) {
                string s = to_string(it.first);
                string s1 = s.substr(0,s.length()/2), s2 = s.substr(s.length() / 2);
                temp[stoll(s1)] += it.second;
                temp[stoll(s2)] += it.second;
            } else  
                temp[2024*it.first] += it.second;
        }
        freq = temp;
    }

    long long ans = 0;
    for(auto& i:freq)
        ans += i.second;
    cout<<ans;

    inputFile.close();
    return 0;
}