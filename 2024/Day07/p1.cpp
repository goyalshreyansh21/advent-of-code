#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool isPossible(vector<long long>& v, int i, long long cur, long long target) {
    if(i == v.size())
        return cur == target;
    return isPossible(v, i+1, cur*v[i], target) || isPossible(v, i+1, cur+v[i], target);
}

int main() {
    ifstream inputFile("text.txt");
    string line;

    long long ans = 0;

    while(getline(inputFile, line)) {
        vector<long long> v;
        long long n = stoll(line.substr(0,line.find(':')));

        line = line.substr(line.find(':')+2);
        stringstream ss(line);
        int temp;
        while (ss >> temp) 
            v.push_back(temp);

        if(isPossible(v, 1, v[0], n))
            ans += n;
    }

    cout<<ans;
    
    inputFile.close();
    return 0;
}