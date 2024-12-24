#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

bool isvalid(int x, int y) {
    return (x>=0 && x<=3 && y>=0 && y<=2 && !(x==3 && y==0));
}

string robot1(string s) {
    unordered_map<char,vector<int>> m = {{'7',{0,0}}, {'8',{1,0}}, {'9',{2,0}}, {'4',{0,1}}, {'5',{1,1}}, {'6',{2,1}}, {'1',{0,2}}, {'2',{1,2}}, {'3',{2,2}}, {'0',{1,3}}, {'A',{2,3}}};

    string direction;
    char cur = 'A';
    for(char& c:s) {
        int x1 = m[cur][0], y1 = m[cur][1], x2 = m[c][0], y2 = m[c][1];
        while(x1!=x2 || y1!=y2) {
            if(x2<x1) { 
                if(y1==3 && x2==0) {
                    direction += string(y1-y2,'^');
                    y1 = y2;
                } else {
                    direction += '<';
                    x1--;
                }
            } else if(y2<y1) {
                direction += '^';
                y1--;
            } else if(y2>y1) {
                if(x1==0 && y2==3) {
                    direction += string(x2-x1,'>');
                    x1 = x2;
                } else {
                    direction += 'v';
                    y1++;
                }
            } else if(x2>x1) {
                direction += '>';
                x1++;
            }
        }
        cur = c;
        direction += 'A';
    }
    return direction;
}

string robot2(string s) {
    unordered_map<char,unordered_map<char,string>> m = 
                {{'A', {{'A',"A"}, {'^',"<A"}, {'v',"<vA"}, {'>',"vA"}, {'<',"v<<A"}}},
                {'^', {{'A',">A"}, {'^',"A"}, {'v',"vA"}, {'>',"v>A"}, {'<',"v<A"}}},
                {'v', {{'A',"^>A"}, {'^',"^A"}, {'v',"A"}, {'>',">A"}, {'<',"<A"}}},
                {'>', {{'A',"^A"}, {'^',"<^A"}, {'v',"<A"}, {'>',"A"}, {'<',"<<A"}}},
                {'<', {{'A',">>^A"}, {'^',">^A"}, {'v',">A"}, {'>',">>A"}, {'<',"A"}}}};

    string direction;
    char cur = 'A';
    for(char& c:s) {
        direction += m[cur][c];
        cur = c;
    }
    return direction;

}

int main() {
    ifstream inputFile("text.txt");
    string line;

    int ans = 0;
    while(getline(inputFile, line)) 
        ans += robot2(robot2(robot1(line))).length() * stoi(line.substr(0,line.length()-1));
    cout << ans;

    inputFile.close();
    return 0;
}