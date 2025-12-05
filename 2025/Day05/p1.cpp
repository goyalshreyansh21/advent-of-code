#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main() {
    ifstream inputFile("text.txt");
    string line;

    map<long long, long long> m;
    while (getline(inputFile, line) && !line.empty()) {
        long long start = stoll(line.substr(0, line.find('-'))), end = stoll(line.substr(line.find('-') + 1));
        m[start] = max(m[start], end);
    }

    map<long long, long long>::iterator it;
    for (it = begin(m); it != end(m);) {
        long long l = it->first, r = it->second;
        map<long long, long long>::iterator nxt = next(it);
        while (nxt != end(m) && nxt->first <= r) {
            r = max(r, nxt->second);
            nxt = m.erase(nxt);
        }
        it->second = r;
        it = nxt;
    }

    int ans = 0;
    while (getline(inputFile, line)) {
        long long check = stoll(line);
        it = m.lower_bound(check);
        if (it->first == check)
            ans++;
        else if (it != m.begin()) {
            it--;
            if (it->second >= check)
                ans++;
        }
    }
    cout << ans;

    inputFile.close();
    return 0;
}