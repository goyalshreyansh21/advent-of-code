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

int generatenext(vector<int> &v)
{
    if(allzeros(v))
        return 0;

    vector<int> temp;
    for(int i=1; i<v.size(); i++)
        temp.push_back(v[i]-v[i-1]);
    int n = generatenext(temp);
    return n + temp[temp.size()-1];
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

        ans += generatenext(v) + v[v.size()-1];
    }
    
    cout<<ans;
    inputFile.close();
    return 0;
}