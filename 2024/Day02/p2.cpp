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
        
        bool canfix = false;
        for(int i=0; i<v.size() && !canfix; i++) {
            vector<int> temp = v;
            temp.erase(temp.begin()+i);
            bool valid = true;
            for(int i=1; i<temp.size() && valid; i++) {
                int diff = temp[i] - temp[i-1];
                if(abs(diff) < 1 || abs(diff) > 3 || (diff > 0 != temp[1] > temp[0]))
                    valid = false;
            }
            if(valid)
                canfix = true;
        }
        
        if(canfix)
            ans++;
    }
        
    cout<<ans;
    
    inputFile.close();
    return 0;
}