#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

int main() {
    ifstream inputFile("text.txt");
    string line;

    unordered_map<int, int> m1, m2;

    while(getline(inputFile, line)) {
        int n1, n2;
        stringstream ss(line);

        ss >> n1 >> n2;
        m1[n1]++;
        m2[n2]++;
    }

    long long ans = 0;
    for(pair<const int, int>& p:m1) 
        ans += p.first * m2[p.first] * p.second;
        
    cout<<ans;
    
    inputFile.close();
    return 0;
}
