#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

int main() {
    ifstream inputFile("text.txt");
    string line;

    getline(inputFile, line);
    vector<long long> dp(line.length());
    dp[line.find('S')]++;

    while (getline(inputFile, line)) {
        vector<long long> temp(line.length());
        for (int i = 0; i < line.length(); i++)
            if (line[i] == '^') {
                if (i)
                    temp[i - 1] += dp[i];
                if (i + 1 < line.length())
                    temp[i + 1] += dp[i];
            } else
                temp[i] += dp[i];
        dp = temp;
    }

    long long ans = accumulate(begin(dp), end(dp), 0LL);
    cout << ans;
    return 0;
}