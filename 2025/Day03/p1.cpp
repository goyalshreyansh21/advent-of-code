#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream inputFile("text.txt");
    string line;

    long long ans = 0;
    while (getline(inputFile, line)) {
        int d = line.back() - '0', best = -1;
        for (int i = line.length() - 2; i >= 0; i--) {
            int cur = line[i] - '0';
            best = max(best, cur * 10 + d);
            d = max(d, cur);
        }
        ans += best;
    }

    cout << ans;

    inputFile.close();
    return 0;
}