

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool valid(vector<string>& grid, int x, int y, int x1, int y1, int x2, int y2) {
    return (((grid[x+x1][y+y1] == 'M' && grid[x-x1][y-y1] == 'S') || (grid[x+x1][y+y1] == 'S' && grid[x-x1][y-y1] == 'M')) && ((grid[x+x2][y+y2] == 'M' && grid[x-x2][y-y2] == 'S') || (grid[x+x2][y+y2] == 'S' && grid[x-x2][y-y2] == 'M')));
}

int main() {
    ifstream inputFile("text.txt");
    string line;
    vector<string> grid;

    while(getline(inputFile, line)) 
        grid.push_back(line);
        
    vector<vector<int>> directions = {{-1,1},{-1,-1},{1,-1},{1,1},{-1,1}};

    int ans = 0;
    for(int i=1; i<grid.size()-1; i++) 
        for(int j=1; j<grid[0].length()-1; j++)
            if(grid[i][j] == 'A')
                for(int k=0; k<4; k++)
                    if(valid(grid,i,j,directions[k][0],directions[k][1], directions[k+1][0], directions[k+1][1]))
                        ans++;
    
    cout<<ans/4;
    
    inputFile.close();
    return 0;
}