#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream inputFile("text.txt");
    string line;

    vector<string> v;
    while (getline(inputFile, line)) {
        if (line[0] == '*' || line[0] == '+')
            break;
        v.push_back(line);
    }

    vector<char> op;
    stringstream ss(line);
    string s;
    while (ss >> s)
        op.push_back(s[0]);

    inputFile.close();

    vector<int> spaces(1, -1);
    for (int j = 0; j < v[0].length(); j++) {
        bool space = true;
        for (int i = 0; i < v.size() && space; i++)
            space &= v[i][j] == ' ';
        if (space)
            spaces.push_back(j);
    }
    spaces.push_back(v[0].length());

    long long ans = 0;
    for (int k = 1; k < spaces.size(); k++) {
        vector<long long> temp(spaces[k] - spaces[k - 1] - 1);
        for (int j = 0; j < temp.size(); j++) {
            for (int i = 0; i < v.size(); i++) {
                if (v[i][spaces[k - 1] + 1 + j] == ' ')
                    continue;
                (temp[j] *= 10) += v[i][spaces[k - 1] + 1 + j] - '0';
            }
        }

        long long cur = op[k - 1] == '*';
        for (int i = 0; i < temp.size(); i++)
            if (op[k - 1] == '+')
                cur += temp[i];
            else
                cur *= temp[i];
        ans += cur;
    }
    cout << ans;
    return 0;
}