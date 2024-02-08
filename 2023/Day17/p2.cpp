#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_set>
using namespace std;

class Move
{
public:
    vector<int> pos;
    vector<int> dir;
    int loss, straight;
    Move(vector<int> v1, vector<int> v2)
    {
        pos = v1;
        dir = v2;
        loss = 0;
        straight = 0;
    }
};

bool operator<(const Move& a, const Move& b) 
{ 
    return a.loss > b.loss; 
}

bool operator==(const Move& a, const Move& b) 
{ 
    return (a.pos==b.pos && a.dir==b.dir && a.straight==b.straight);
}

vector<int> operator+(vector<int> vec1, vector<int> vec2) 
{
        vector<int> result = vec2;
        for(int i = 0; i<vec1.size(); i++) 
            result[i] += vec1[i];
        return result;
}

int cantor(int a, int b)
{ 
    return (a+b+1) * (a+b) / 2 + b; 
}

vector<int> rotate_cw(vector<int> dir) 
{ 
    return {-dir[1],dir[0]}; 
}

vector<int> rotate_ccw(vector<int> dir) 
{ 
    return {dir[1],-dir[0]}; 
}

struct move_hash {
    size_t operator()(const Move& move) const {
        return cantor(move.pos[0], cantor(move.pos[1], cantor(move.dir[0], cantor(move.dir[1], move.straight))));
    }
};

int main() 
{
    ifstream inputFile("text.txt");
    string line;

    vector<vector<int>> lavafall;
    while(getline(inputFile, line))
    {
        vector<int> l;
        for(char c:line)
            l.push_back(c-'0');
        lavafall.push_back(l);
    }

    priority_queue<Move> q;
    unordered_set<Move,move_hash> visited;

    vector<int> dst = {(int)lavafall.size()-1, (int)lavafall[0].size()-1};

    q.push(Move({0,0},{0,1}));
    q.push(Move({0,0},{1,0}));

    while (!q.empty()) 
    {
        Move curr = q.top();
        q.pop();

        if (visited.count(curr)) 
            continue;
        visited.insert(curr);

        if(curr.pos == dst && curr.straight>=3)
        {
            cout<<curr.loss;
            break;
        }

        vector<int> dir, pos;

        if(curr.straight>=3)
        {
            dir = rotate_ccw(curr.dir); 
            pos = curr.pos + dir;
            if(pos[0]>=0 && pos[0]<lavafall.size() && pos[1]>=0 && pos[1]<lavafall[0].size()) 
            {
                Move move = Move(pos,dir);
                move.loss = curr.loss + lavafall[pos[0]][pos[1]];
                q.push(move);
            }

            dir = rotate_cw(curr.dir); 
            pos = curr.pos + dir;
            if(pos[0]>=0 && pos[0]<lavafall.size() && pos[1]>=0 && pos[1]<lavafall[0].size()) 
            {
                Move move = Move(pos,dir);
                move.loss = curr.loss + lavafall[pos[0]][pos[1]];
                q.push(move);
            }
        }

        if(curr.straight<9)
        {
            vector<int> pos = curr.pos + curr.dir;
            if(pos[0]>=0 && pos[0]<lavafall.size() && pos[1]>=0 && pos[1]<lavafall[0].size()) 
            {
                Move move = Move(pos,curr.dir);
                move.loss = curr.loss + lavafall[pos[0]][pos[1]];
                move.straight = curr.straight+1;
                q.push(move);
            }
        }
    }

    inputFile.close();
    return 0;
}