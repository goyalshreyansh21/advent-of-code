#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream inputFile("text.txt");
    string line;
    int cur = 50, ans = 0;

    while (getline(inputFile, line)) {
        int sign = line[0] == 'R' ? 1 : -1;
        int offset = stoi(line.substr(1));
        (cur += offset * sign) %= 100;
        if (cur == 0)
            ans++;
    }

    cout << ans;

    inputFile.close();
    return 0;
}
