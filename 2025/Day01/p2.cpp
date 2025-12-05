#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    ifstream inputFile("text.txt");
    string line;
    int cur = 50, ans = 0;

    while (getline(inputFile, line)) {
        int sign = line[0] == 'R' ? 1 : -1;
        int offset = stoi(line.substr(1));

        int rotations = offset / 100;
        offset %= 100;
        ans += rotations;

        if (sign == 1) {
            if (cur + offset >= 100)
                ans++;
        }
        else if (cur > 0 && offset >= cur)
            ans++;

        cur += offset * sign;
        ((cur %= 100) += 100) %= 100;
    }

    cout << ans;

    inputFile.close();
    return 0;
}
