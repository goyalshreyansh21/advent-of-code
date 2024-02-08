#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

bool allzeros(vector<int> &v)
{
    for(int i:v)
    {
        if(i)
            return false;
    }
    return true;
}

int generateprev(vector<int> &v)
{
    if(allzeros(v))
        return 0;

    vector<int> temp;
    for(int i=1; i<v.size(); i++)
        temp.push_back(v[i]-v[i-1]);
    int n = generateprev(temp);
    return temp[0] - n;
}

int main() 
{
    ifstream inputFile("text.txt");
    string line;
    int ans = 0;

    while (getline(inputFile, line)) 
    {
        istringstream iss(line);
        vector<int> v;

        int n;
        while (iss >> n)
            v.push_back(n);

        ans += v[0] - generateprev(v);
    }
    
    cout<<ans;
    inputFile.close();
    return 0;
}