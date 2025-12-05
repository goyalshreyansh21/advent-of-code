#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
    ifstream inputFile("text.txt");
    string line;

    vector<pair<long long, long long>> v;
    while (getline(inputFile, line) && !line.empty()) {
        long long start = stoll(line.substr(0, line.find('-'))), end = stoll(line.substr(line.find('-') + 1));
        v.push_back({start, end});
    }

    inputFile.close();

    sort(begin(v), end(v));
    long long ans = 0, l = v[0].first, r = v[0].second;
    for (int i = 1; i < v.size(); i++) {
        long long curl = v[i].first, curr = v[i].second;
        if (curl <= r)
            r = max(r, curr);
        else {
            ans += r - l + 1;
            r = curr;
            l = curl;
        }
    }
    ans += r - l + 1;
    cout << ans;
    return 0;
}