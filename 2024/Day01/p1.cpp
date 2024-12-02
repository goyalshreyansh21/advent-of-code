#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    ifstream inputFile("text.txt");
    string line;

    vector<int> v1, v2;

    while(getline(inputFile, line)) {
        int n1, n2;
        stringstream ss(line);

        ss >> n1 >> n2;
        v1.push_back(n1);
        v2.push_back(n2);
    }

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    long long ans = 0;
    for(int i=0; i<v1.size(); i++) 
        ans += abs(v1[i] - v2[i]);
        
    cout<<ans;
    
    inputFile.close();
    return 0;
}
