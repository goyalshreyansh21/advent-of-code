#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ifstream inputFile("text.txt");
    string line;

    long long ans = 0;
    while(getline(inputFile, line)) {
        long long n = stoll(line);
        for(int i=0; i<2000; i++) {
            n = ((n*64) ^ n) % 16777216;
            n = (n/32 ^ n) % 16777216;
            n = ((n*2048) ^ n) % 16777216;
        }
        ans += n;
    } 

    cout << ans;

    inputFile.close();
    return 0;
}