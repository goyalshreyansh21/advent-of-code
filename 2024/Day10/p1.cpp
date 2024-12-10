#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

int main() 
{
    ifstream inputFile("text.txt");
    string line;
    vector<vector<int>> grid;

    while(getline(inputFile, line)) {
        vector<int> row;
        for(char& c:line)
            row.push_back(c-'0');
        grid.push_back(row);
    }

    int ans = 0;
    for(int i=0; i<grid.size(); i++) {
        for(int j=0; j<grid[0].size(); j++) {
            if(grid[i][j] == 0) {
                vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size()));
                visited[i][j] = true;
                
                queue<vector<int>> q;
                q.push({i,j,0});
                
                while(!q.empty()) {
                    int x = q.front()[0], y = q.front()[1], cur = q.front()[2];
                    q.pop();

                    if(cur == 9) {
                        ans++;
                        continue;
                    }

                    if(x > 0 && grid[x-1][y] == cur+1 && !visited[x-1][y]) {
                        visited[x-1][y] = true;
                        q.push({x-1,y,cur+1});
                    }
                        
                    if(x < grid.size()-1 && grid[x+1][y] == cur+1 && !visited[x+1][y]){
                        visited[x+1][y] = true;
                        q.push({x+1,y,cur+1});
                    }
                    
                    if(y > 0 && grid[x][y-1] == cur+1 && !visited[x][y-1]){
                        visited[x][y-1] = true;
                        q.push({x,y-1,cur+1});
                    }

                    if(y < grid[0].size()-1 && grid[x][y+1] == cur+1 && !visited[x][y+1]){
                        visited[x][y+1] = true;
                        q.push({x,y+1,cur+1});
                    }

                }
            }
        }
    }

    cout<<ans;

    inputFile.close();
    return 0;
}