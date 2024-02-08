#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Point
{
public:
    float x, y, vx, vy;
    float m, c;
    Point(float x1, float y1, float v1, float v2) 
    {
        x=x1;
        y=y1;
        vx=v1;
        vy=v2;
        m = vy/vx;
        c = y - x * vy/vx; 
    }
};

int main() 
{
    ifstream inputFile("text.txt");
    string line;

    vector<Point> v;
    while(getline(inputFile, line))
    {
        istringstream iss(line);
        string px, py, pz, vx, vy, vz;
        getline(iss, px, ',');
        getline(iss, py, ',');
        getline(iss, pz, '@');
        getline(iss, vx, ',');
        getline(iss, vy, ',');
        getline(iss, vz);
        v.push_back(Point(stof(px),stof(py),stof(vx),stof(vy)));
    }

    int ans = 0;
    for(int i=0; i<v.size(); i++)
    {
        for(int j=i+1; j<v.size(); j++)
        {
            Point p1 = v[i], p2 = v[j];
            if(p1.m==p2.m)
                continue;
            
            double x = (p2.c - p1.c) / (p1.m - p2.m);
            double y = p1.m * x + p1.c;
            if(((x-p1.x)/p1.vx < 0) || ((x-p2.x)/p2.vx < 0) || ((y-p1.y)/p1.vy < 0) || ((y-p2.y)/p2.vy < 0))
                continue;

            if((x<=400000000000000) && (x>=200000000000000) && (y<=400000000000000) && (y>=200000000000000))
                ans++;
        }
    }

    cout<<ans;
    inputFile.close();
    return 0;
}