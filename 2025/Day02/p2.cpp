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
        for (long long i = stoll(start); i <= stoll(end); i++) {
            string temp = to_string(i);
            if (temp.length() <= 1)
                continue;
            string rep = temp + temp;
            rep = rep.substr(1, rep.length() - 2);
            if (rep.find(temp) != string::npos)
                ans += i;
        }
    }
    cout << ans;

    return 0;
}