#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main() {
    ifstream inputFile("text.txt");
    string line;
    regex pattern(R"(mul\(([0-9]{1,3}),([0-9]{1,3})\))");

    long long ans = 0;
    bool ignore = false;
    while(getline(inputFile, line)) {
        int l = ignore ? line.find("do()") : 0, r = line.find("don't()", l);
        while(l != string::npos) {
            ignore = r != string::npos;
            r = (r == string::npos) ? line.size() : r;
            sregex_iterator next=sregex_iterator(line.begin()+l, line.begin()+r, pattern);
            sregex_iterator end;
            
            while(next != end) {
                smatch match = *next;
                ans += stoi(match[1].str()) * stoi(match[2].str());
                next++;
            }

            l = line.find("do()", r+1);
            r = line.find("don't()",l);
        }
    }
        
    cout<<ans;
    
    inputFile.close();
    return 0;
}