#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

bool isvalid(int x, int y) {
    return (x>=0 && x<=3 && y>=0 && y<=2 && !(x==3 && y==0));
}

string movenum(char& from, char& to) {
    unordered_map<char,vector<int>> m = {{'7',{0,0}}, {'8',{1,0}}, {'9',{2,0}}, {'4',{0,1}}, {'5',{1,1}}, {'6',{2,1}}, {'1',{0,2}}, {'2',{1,2}}, {'3',{2,2}}, {'0',{1,3}}, {'A',{2,3}}};

    string direction;
    int x1 = m[from][0], y1 = m[from][1], x2 = m[to][0], y2 = m[to][1];
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
    direction += 'A';
    return direction;
}

void robot1(string s, unordered_map<string,long long>& freq) {
    char cur = 'A';
    for(char& c:s) {
        string direction = movenum(cur,c);
        cur = c;
        freq[direction]++;
    }
}

void movedir(string s, long long n, unordered_map<string,long long>& freq) {
    unordered_map<char,unordered_map<char,string>> m = 
                {{'A', {{'A',"A"}, {'^',"<A"}, {'v',"<vA"}, {'>',"vA"}, {'<',"v<<A"}}},
                {'^', {{'A',">A"}, {'^',"A"}, {'v',"vA"}, {'>',"v>A"}, {'<',"v<A"}}},
                {'v', {{'A',"^>A"}, {'^',"^A"}, {'v',"A"}, {'>',">A"}, {'<',"<A"}}},
                {'>', {{'A',"^A"}, {'^',"<^A"}, {'v',"<A"}, {'>',"A"}, {'<',"<<A"}}},
                {'<', {{'A',">>^A"}, {'^',">^A"}, {'v',">A"}, {'>',">>A"}, {'<',"A"}}}};


    char cur = 'A';
    for(char& c:s) {
        string direction = m[cur][c];
        freq[direction] += n;
        cur = c;
    }
}

void robot2(unordered_map<string,long long>& freq) {
    unordered_map<string, long long> temp = freq;
    for(pair<const string, long long>&p:temp) {
        movedir(p.first, p.second, freq);
        freq[p.first] -= p.second;
    }
}

int main() {
    ifstream inputFile("text.txt");
    string line;

    long long ans = 0;
    while(getline(inputFile, line)) {
        unordered_map<string,long long> freq;
        robot1(line, freq);
        for(int i=0; i<25; i++) 
            robot2(freq);
        
        long long cur = 0;
        for(pair<const string, long long>&p:freq) 
            cur += p.first.length() * p.second;

        ans += cur*stoll(line.substr(0,line.length()-1));
    } 
    


    cout << ans;

    inputFile.close();
    return 0;
}