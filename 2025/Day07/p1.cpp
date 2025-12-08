#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <utility>

using namespace std;

int main() {
    ifstream inputFile("text.txt");

    string line;
    vector<string> v;

    while (getline(inputFile, line))
        v.push_back(line);

    inputFile.close();

    function<int(int, int)> hash = [](int x, int y) {
        return x * 1000 + y;
    };
    function<pair<int, int>(int)> unhash = [](int n) {
        return make_pair(n / 1000, n % 1000);
    };

    unordered_set<int> s;

    queue<int> q;
    q.push(hash(1, v[0].find('S')));

    while (!q.empty()) {
        pair<int, int> p = unhash(q.front());
        q.pop();
        int x = p.first, y = p.second;
        while (x < v.size() && v[x][y] == '.') {
            v[x][y] = '|';
            x++;
        }
        if (x < v.size() && v[x][y] == '^') {
            s.insert(hash(x, y));
            if (y + 1 < v[0].size())
                q.push(hash(x, y + 1));
            if (y > 0)
                q.push(hash(x, y - 1));
        }
    }

    int ans = s.size();
    cout << ans;
    return 0;
}