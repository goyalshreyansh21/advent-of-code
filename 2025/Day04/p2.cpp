#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

int main() {
    ifstream inputFile("text.txt");
    string line;
    vector<string> grid;
    while (getline(inputFile, line))
        grid.push_back(line);
    inputFile.close();

    vector<vector<int>> directions = {{0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}, {1, 1}, {1, -1}, {1, 0}};

    function<bool(int, int)> valid = [&](int i, int j) {
        return (i >= 0 && i < grid.size() && j >= 0 && j < grid[0].length());
    };

    int ans = 0, cur = 0;
    do {
        cur = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].length(); j++) {
                if (grid[i][j] == '@') {
                    int c = 0;
                    for (vector<int> &d : directions)
                        if (valid(i + d[0], j + d[1]) && grid[i + d[0]][j + d[1]] == '@')
                            c++;
                    if (c < 4) {
                        cur++;
                        grid[i][j] = '.';
                    }
                }
            }
        }
        ans += cur;
    } while (cur);

    cout << ans;
    return 0;
}