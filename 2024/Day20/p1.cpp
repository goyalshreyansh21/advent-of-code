#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

bool isValid(int x, int y, vector<vector<int>>& distance) {
    return (x>=0 && x<distance.size() && y>=0 && y<distance[0].size());
}

vector<vector<int>> calcDist(vector<string>& grid) {
    vector<vector<int>> distance(grid.size(), vector<int>(grid[0].length(),-1));
    vector<int> directions = {0,1,0,-1,0};

    int startx = -1, starty = -1;
    for(int i=0; i<grid.size() && startx == -1; i++) {
        for(int j=0; j<grid[0].length() && startx == -1; j++) {
            if(grid[i][j] == 'S') {
                startx = i;
                starty = j;
            }
        }
    }

    queue<pair<int,int>> q;
    q.push({startx, starty});

    distance[startx][starty] = 0;
    int dist = 1;
    while(!q.empty()) {
        int s = q.size();
        while(s--) {
            int x = q.front().first, y = q.front().second;
            q.pop();

            for(int i=0; i<4; i++) {
                int dx = x + directions[i], dy = y + directions[i+1];
                if(isValid(dx,dy,distance) && distance[dx][dy]==-1 && grid[dx][dy]!='#') {
                    distance[dx][dy] = dist;
                    q.push({dx,dy});
                }
            }
        }
        dist++;
    }
    return distance;
}

pair<pair<int,int>,pair<int,int>> shortcut(vector<vector<int>>& distance) {
    vector<int> directions = {0,2,0,-2,0};

    int mx = 0;
    pair<pair<int,int>,pair<int,int>> p;

    for(int i=0; i<distance.size(); i++) {
        for(int j=0; j<distance[0].size(); j++) {
            for(int k=0; k<4; k++) {
                if(distance[i][j] == -1)
                    continue;

                int dx = i + directions[k], dy = j + directions[k+1];
                if(isValid(dx,dy,distance) && distance[dx][dy]!=-1 && distance[dx][dy]-distance[i][j] > mx) {
                    mx = distance[dx][dy]-distance[i][j];
                    p = {{i,j}, {dx,dy}};
                }
            }
        }
    }
    return p;
}

int main() {
    ifstream inputFile("text.txt");
    string line;

    vector<string> grid;
    while(getline(inputFile, line)) 
        grid.push_back(line);

    vector<vector<int>> distance(grid.size(), vector<int>(grid[0].length(),-1));
    vector<int> directions = {0,1,0,-1,0};

    int startx = -1, starty = -1;
    for(int i=0; i<grid.size() && startx == -1; i++) {
        for(int j=0; j<grid[0].length() && startx == -1; j++) {
            if(grid[i][j] == 'S') {
                startx = i;
                starty = j;
            }
        }
    }

    queue<pair<int,int>> q;
    q.push({startx, starty});

    distance[startx][starty] = 0;
    int dist = 1;
    while(!q.empty()) {
        int s = q.size();
        while(s--) {
            int x = q.front().first, y = q.front().second;
            q.pop();

            for(int i=0; i<4; i++) {
                int dx = x + directions[i], dy = y + directions[i+1];
                if(isValid(dx,dy,distance) && distance[dx][dy]==-1 && grid[dx][dy]!='#') {
                    distance[dx][dy] = dist;
                    q.push({dx,dy});
                }
            }
        }
        dist++;
    }

    int ans = 0;
    vector<int> jump = {0,2,0,-2,0};

    for(int i=0; i<distance.size(); i++) {
        for(int j=0; j<distance[0].size(); j++) {
            if(distance[i][j] == -1)
                continue;

            for(int k=0; k<4; k++) {

                int dx = i + jump[k], dy = j + jump[k+1];
                if(isValid(dx,dy,distance) && distance[dx][dy]!=-1 && distance[dx][dy]-distance[i][j]-2 >= 100) 
                    ans++;
            }
        }
    }
    cout << ans;

    inputFile.close();
    return 0;
}