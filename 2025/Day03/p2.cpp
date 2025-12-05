#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream inputFile("text.txt");
    string line;

    long long ans = 0;
    while (getline(inputFile, line)) {
        int drop = line.length() - 12;
        string s;
        for (char &c : line) {
            while (!s.empty() && drop && s.back() < c) {
                drop--;
                s.pop_back();
            }
            s.push_back(c);
        }
        ans += stoll(s.substr(0, 12));
    }

    cout << ans;

    inputFile.close();
    return 0;
}