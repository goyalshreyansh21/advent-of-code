#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool valid(vector<string>& grid, int x, int y, int xdir, int ydir) {
    if(x+3*xdir < 0 || x+3*xdir > grid.size() || y+3*ydir < 0 || y+3*ydir > grid[0].length())
        return false;
    
    return ((grid[x+xdir][y+ydir] == 'M') && (grid[x+2*xdir][y+2*ydir] == 'A') && (grid[x+3*xdir][y+3*ydir] == 'S'));
}

int main() {
    ifstream inputFile("text.txt");
    string line;
    vector<string> grid;

    while(getline(inputFile, line)) 
        grid.push_back(line);
        
    vector<vector<int>> directions = {{0,1},{0,-1},{-1,1},{-1,0},{-1,-1},{1,1},{1,-1},{1,0}};

    int ans = 0;
    for(int i=0; i<grid.size(); i++) 
        for(int j=0; j<grid[0].length(); j++)
            if(grid[i][j] == 'X')
                for(int k=0; k<8; k++)
                    if(valid(grid,i,j,directions[k][0],directions[k][1]))
                        ans++;
    
    cout<<ans;
    
    inputFile.close();
    return 0;
}