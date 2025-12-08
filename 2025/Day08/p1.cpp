#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

int find(vector<int> &v, int x) {
    return v[x] = (v[x] == x ? v[x] : find(v, v[x]));
}

void dsu(vector<int> &v, int x, int y) {
    x = find(v, x);
    y = find(v, y);
    v[x] = y;
}

int main() {
    ifstream inputFile("text.txt");
    string line;
    vector<vector<int>> v;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string s;
        v.push_back({});
        while (getline(ss, s, ','))
            v.back().push_back(stoi(s));
    }
    inputFile.close();

    function<long long(int, int)> calc = [&](int i, int j) {
        return pow(v[i][0] - v[j][0], 2) + pow(v[i][1] - v[j][1], 2) + pow(v[i][2] - v[j][2], 2);
    };

    vector<vector<long long>> dist;
    for (int i = 0; i < v.size(); i++)
        for (int j = i + 1; j < v.size(); j++)
            dist.push_back({calc(i, j), i, j});

    sort(begin(dist), end(dist));
    vector<int> parent(v.size());
    for (int i = 0; i < v.size(); i++)
        parent[i] = i;

    int i = 0;
    while (i < 1000) {
        dsu(parent, dist[i][1], dist[i][2]);
        i++;
    }

    vector<int> count(v.size());
    for (int i = 0; i < v.size(); i++)
        count[find(parent, i)]++;

    sort(begin(count), end(count), greater());
    int ans = 1;
    for (int i = 0; i < 3; i++)
        ans *= count[i];
    cout << ans;
    return 0;
}