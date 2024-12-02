#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    ifstream inputFile("text.txt");
    string line;

    int ans = 0;
    while(getline(inputFile, line)) {
        vector<int> v;
        stringstream ss(line);
        int n;

        while(ss >> n)
            v.push_back(n);
        
        bool valid = true;
        for(int i=1; i<v.size() && valid; i++) {
            int diff = v[i] - v[i-1];
            if(abs(diff) < 1 || abs(diff) > 3 || (diff > 0 != v[1] > v[0]))
                valid = false;
        }
        
        if(valid)
            ans++;
    }
        
    cout<<ans;
    
    inputFile.close();
    return 0;
}