#include <iostream>
#include <fstream>
using namespace std;

class Lens
{
public:
    string label;
    int flen;
    Lens(string s, int n)
    {
        label = s;
        flen = n;
    }
};

int hashvalue(string s)
{
    int h = 0;
    for(char c:s)
        h = (h+c)*17 % 256;
    return h;
}

int main() 
{
    ifstream inputFile("text.txt");
    string pattern;
    vector<vector<Lens>> boxes(256);

    while(getline(inputFile, pattern, ','))
    {
        if(pattern.back()=='-')
        {
            string label = pattern.substr(0, pattern.find('-'));
            int box = hashvalue(label);
            for(int i=0; i<boxes[box].size(); i++)
            {
                if(boxes[box][i].label == label)
                {
                    boxes[box].erase(boxes[box].begin()+i);
                    break;
                }
            }
        }
        else
        {
            string label = pattern.substr(0, pattern.find('='));
            int n = stoi(pattern.substr(pattern.find('=') + 1));
            int box = hashvalue(label);
            bool exists = false;
            for(int i=0; i<boxes[box].size(); i++)
            {
                if(boxes[box][i].label == label)
                {
                    boxes[box][i].flen = n;
                    exists = true;
                    break;
                }
            }
            if(!exists)
                boxes[hashvalue(label)].push_back(Lens(label,n));
        }
    }

    long long ans = 0;
    for(int i=0; i<256; i++)
    {
        for(int j=0; j<boxes[i].size(); j++)
            ans += (i+1)*(j+1)*boxes[i][j].flen;
    }

    cout<<ans;
    inputFile.close();
    return 0;
}