#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream inputFile("text.txt");
    string line;

    vector<vector<long long>> v;
    while (getline(inputFile, line)) {
        if (line[0] == '*' || line[0] == '+')
            break;
        stringstream ss(line);
        string s;
        vector<long long> temp;
        while (ss >> s)
            temp.push_back(stoll(s));
        v.push_back(temp);
    }

    vector<char> op;
    stringstream ss(line);
    string s;
    while (ss >> s)
        op.push_back(s[0]);

    inputFile.close();

    long long ans = 0;
    for (int j = 0; j < v[0].size(); j++) {
        long long cur = op[j] == '*';
        for (int i = 0; i < v.size(); i++)
            if (op[j] == '+')
                cur += v[i][j];
            else
                cur *= v[i][j];
        ans += cur;
    }
    cout << ans;
    return 0;
}