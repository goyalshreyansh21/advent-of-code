#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
    ifstream inputFile("text.txt");
    string line;

    unordered_set<string> s;
    bool parse = true;

    int ans = 0;

    while(getline(inputFile, line)) {
        if(line.empty())
            parse = false;
        
        if(parse) {
            s.insert(line);
        } else if(!line.empty()) {
            vector<int> numbers;
            replace(line.begin(), line.end(), ',', ' ');
            istringstream ss(line);
            int n;
            while (ss >> n) 
                numbers.push_back(n);

            bool valid = true;
            for(int i=0; i<numbers.size() && valid; i++) 
                for(int j=i+1; j<numbers.size() && valid; j++) 
                    if(s.count(to_string(numbers[j]) + "|" + to_string(numbers[i])))
                        valid = false;
            
            if(valid) 
                ans += numbers[numbers.size()/2];
        }
    }

    cout<<ans;
    
    inputFile.close();
    return 0;
}