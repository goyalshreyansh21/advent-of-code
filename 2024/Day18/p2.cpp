#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

bool isPossible(int n) {
    ifstream inputFile("text.txt");
    string line;
    vector<string> grid(71, string(71,'.'));
    
    for(int i=0; i<n; i++) {
        getline(inputFile, line);
        int x = stoi(line.substr(0,line.find(','))), y = stoi(line.substr(line.find(',')+1));
        grid[x][y] = '#';
    }

    vector<int> directions = {0,1,0,-1,0};
    queue<pair<int,int>> q;
    q.push({0,0});

    vector<vector<int>> distance(71, vector<int>(71,-1));
    distance[0][0] = 0;
    int dist = 1;
    while(!q.empty()) {
        int s = q.size();
        while(s--) {
            int x = q.front().first, y = q.front().second;
            q.pop();

            for(int i=0; i<4; i++) {
                int dx = x + directions[i], dy = y + directions[i+1];
                if(dx>=0 && dx<71 && dy>=0 && dy<71 && distance[dx][dy]==-1 && grid[dx][dy] == '.') {
                    distance[dx][dy] = dist;
                    q.push({dx,dy});
                }
            }
        }
        dist++;
    }

    return distance[70][70] != -1;
}

int main() {
    int l = 1, r = 3450;
    while(l<r) {
        int mid = (l+r)/2;
        if(isPossible(mid))
            l = mid+1;
        else
            r = mid;
    }

    ifstream inputFile("text.txt");
    string line;
    for(int i=0; i<l; i++) 
        getline(inputFile, line);
    cout << line;
    inputFile.close();
    return 0;
}