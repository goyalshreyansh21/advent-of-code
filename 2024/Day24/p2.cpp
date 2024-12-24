#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    ifstream inputFile("text.txt");
    string line;

    unordered_map<string, int> val;
    while(getline(inputFile, line) && !line.empty()) 
        val[line.substr(0,3)] = line.back()-'0';
    
    unordered_map<string, vector<string>> m;
    while(getline(inputFile, line)) {
        string in1 = line.substr(0,3);
        
        line = line.substr(4);
        string op = line.substr(0,line.find(' '));
        
        line = line.substr(line.find(' ')+1);
        string in2 = line.substr(0,3);

        string out = line.substr(7);
        m[out] = {in1,in2,op};
    }

    // xn ^ yn -> XYADD[n]
    // xn & yn -> XYCARRY[n]
    // XYADD[n] ^ CARRY[n - 1] -> Zn
    // XYADD[n] & CARRY[n - 1] -> ANDS[$n] 
    // XYCARRY[n] | ANDS[$n] -> CARRY[n]

    vector<string> xyAdds, xyCarries, zOuts, ands, carries, wrongs;
    for(pair<const string, vector<string>>& p:m) {
        string a = p.second[0], b = p.second[1], op = p.second[2];
        if(a[0] == 'x' || a[0] == 'y' || b[0] == 'x' || b[0] == 'y') 
            (op == "AND" ? xyCarries : xyAdds).push_back(p.first);
        else
            (op == "AND" ? ands : op == "XOR" ? zOuts : carries).push_back(p.first);
    }

    for(string& s:xyAdds) {
        if(m[s][0] == "x00" || m[s][0] == "y00")
            continue; 

        bool isValid = true, foundInXor = false;
        if(s[0] == 'z')
            isValid = false;
        for(string& t:zOuts) {
            if(m[t][0] == s || m[t][1] == s) {
                foundInXor = true;
                break;
            }
        }
        if(!foundInXor)
            isValid = false;

        if(!isValid) 
            wrongs.push_back(s);
    }

    for(string& s:xyCarries) {
        if(m[s][0] == "x00" || m[s][0] == "y00")
            continue; 

        bool isValid = true, foundInXor = false;
        if(s[0] == 'z')
            isValid = false;
        for(string& t:carries) {
            if(m[t][0] == s || m[t][1] == s) {
                foundInXor = true;
                break;
            }
        }
        if(!foundInXor)
            isValid = false;

        if(!isValid) 
            wrongs.push_back(s);
    }

    for(string& s:zOuts)
        if(s[0] != 'z')
            wrongs.push_back(s); 

    for(string& s:ands)
        if(s[0] == 'z')
            wrongs.push_back(s); 

    for(string& s:carries)
        if(s[0] == 'z' && s != "z45")
            wrongs.push_back(s);

    sort(begin(wrongs), end(wrongs));
    string ans;
    for(string& s:wrongs)
        ans += s + ',';
    ans.pop_back();
    cout << ans;

    inputFile.close();
    return 0;
}