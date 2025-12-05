#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    ifstream inputFile("text.txt");

    string line;
    getline(inputFile, line);

    inputFile.close();

    stringstream ss(line);

    long long ans = 0;
    string s;
    while (getline(ss, s, ',')) {
        string start = s.substr(0, s.find('-')), end = s.substr(s.find('-') + 1);
        long long l = stoll(start), r = stoll(end), i = start.length() == 1 ? 0 : stoll(start.substr(0, start.length() / 2));
        do {
            long long temp = stoll(to_string(i) + to_string(i));
            if (temp > r)
                break;
            if (temp >= l)
                ans += temp;
            i++;
        } while (true);
    }
    cout << ans;

    return 0;
}