#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

bool isvalid(int x, int y, vector<string>& grid) {
    return (x<grid.size() && x>=0 && y<grid[0].length() && y>=0 && grid[x][y] != '#');
}

int main() 
{
    ifstream inputFile("text.txt");
    string line;

    vector<string> grid;
    while(getline(inputFile, line)) 
        grid.push_back(line);

    int x = -1, y = -1;
    for(int i=0; i<grid.size() && x==-1; i++) {
        for(int j=0; j<grid[0].length() && x==-1; j++) {
            if(grid[i][j] == 'S') {
                x = i;
                y = j;
            }
        }
    }

    vector<int> directions = {0,1,0,-1,0};
    
    vector<vector<vector<int>>> distance(grid.size(), vector<vector<int>>(grid[0].length(), vector<int>(4, INT_MAX)));
    distance[x][y][0] = 0;

    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    pq.push({0,x,y,0});

    while(!pq.empty()) {
        int dist = pq.top()[0], i = pq.top()[1], j = pq.top()[2], dir = pq.top()[3];
        pq.pop();

        if(dist > distance[i][j][dir])
            continue;

        int dx = i + directions[dir], dy = j + directions[dir+1];
        if(isvalid(dx, dy, grid) && distance[dx][dy][dir] > 1+dist) {
            distance[dx][dy][dir] = dist + 1;
            pq.push({1+dist, dx, dy, dir});
        }

        dx = i + directions[(dir+1)%4];
        dy = j + directions[(dir+1)%4+1];
        if(isvalid(dx, dy, grid) && distance[dx][dy][(dir+1)%4] > 1001+dist) {
            distance[dx][dy][(dir+1)%4] = dist + 1001;
            pq.push({1001+dist, dx, dy, (dir+1)%4});
        }

        dx = i + directions[(dir+3)%4];
        dy = j + directions[(dir+3)%4+1];
        if(isvalid(dx, dy, grid) && distance[dx][dy][(dir+3)%4] > 1001+dist) {
            distance[dx][dy][(dir+3)%4] = dist + 1001;
            pq.push({1001+dist, dx, dy, (dir+3)%4});
        }
    }
    
    int ans = INT_MAX;
    for(int i=0; i<grid.size(); i++) 
        for(int j=0; j<grid[0].length(); j++) 
            if(grid[i][j] == 'E') 
                for(int k=0; k<4; k++)
                    ans = min(ans, distance[i][j][k]);
    cout << ans;

    inputFile.close();
    return 0;
}