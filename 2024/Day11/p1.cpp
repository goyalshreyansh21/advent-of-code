#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main() 
{
    ifstream inputFile("text.txt");
    string line;

    getline(inputFile, line);
    stringstream ss(line);
    int n;

    vector<long long> ans;
    while(ss >> n)
        ans.push_back(n);
    
    for(int i=0; i<25; i++) {
        for(int j=ans.size()-1; j>=0; j--) {
            if(ans[j] == 0)
                ans[j] = 1;
            else if(to_string(ans[j]).length() % 2 == 0) {
                string s = to_string(ans[j]);
                string s1 = s.substr(0,s.length()/2), s2 = s.substr(s.length() / 2);
                ans[j] = stoll(s2);
                ans.push_back(stoll(s1));
            } else  
                ans[j] *= 2024;
        }
    }

    cout<<ans.size();

    inputFile.close();
    return 0;
}