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
    while(getline(inputFile, line)) {
        sregex_iterator next=sregex_iterator(line.begin(), line.end(), pattern);
        sregex_iterator end;
        
        while(next != end) {
            smatch match = *next;
            ans += stoi(match[1].str()) * stoi(match[2].str());
            next++;
        }
    }
        
    cout<<ans;
    
    inputFile.close();
    return 0;
}