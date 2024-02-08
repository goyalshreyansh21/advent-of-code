#include <iostream>
#include <fstream>
#include <set>
using namespace std;

class Point
{
public:
    int x, y, z;
    bool operator<(const Point& p) const 
    {
        if(z!=p.z)
            return z < p.z;
        if(x!=p.x)
            return x < p.x;
        return y < p.y;
    }

    Point(int i, int j, int k)
    {
        x=i;
        y=j;
        z=k;
    }
    Point() {}
};

class Line
{
public:
    Point a, b;
	set<int> supportedBy, supports;

	Line(const Point &p1, const Point &p2)
	{
        a = p1<p2 ? p1 : p2;
        b = p1<p2 ? p2 : p1;
	}

	void Drop(int by) 
    { 
        a.z -= by; 
        b.z -= by; 
    }

	bool operator <(const Line& l) const
    { 
        if(a<l.a)
            return true;
        if(l.a<a)
            return false;
        return b < l.b; 
    }
	bool Intersects(const Line& l) const 
    { 
        return !(l.b.x < a.x || l.a.x > b.x || l.b.y < a.y || l.a.y > b.y); 
    }
};

Point sep(string input)
{
    int pos1 = input.find(','), pos2 = input.find(',', pos1 + 1);

    int x = std::stoi(input.substr(0, pos1));
    int y = std::stoi(input.substr(pos1 + 1, pos2 - pos1 - 1));
    int z = std::stoi(input.substr(pos2 + 1));
    return Point(x,y,z);
}

int main() 
{
    ifstream inputFile("test.txt");
    string line;

    vector<Line> lines, settled;
    vector<int> safe;

    while(getline(inputFile, line))
    {
        string fp = line.substr(0,line.find('~'));
        string sp = line.substr(line.find('~')+1);
        lines.push_back(Line(sep(fp),sep(sp)));
    }

    sort(lines.begin(),lines.end());

	for (Line l:lines)
	{
		int highestZ = 0;
		set<int> support;
		for(int i=0; i<settled.size(); i++)
		{
        	if(settled[i].Intersects(l))
			{
				if(settled[i].b.z > highestZ)
				{
					highestZ = settled[i].b.z;
					support = {i};
				}
				else if(settled[i].b.z == highestZ)
					support.insert(i);
			}
        }
		int delta = l.a.z - highestZ - 1;
		l.Drop(delta);
		for(int i:support)
			settled[i].supports.insert(settled.size());
		l.supportedBy = support;
		settled.push_back(l);
		safe.push_back(1);
	}

    for (int i = 0; i < settled.size(); ++i)
		if (settled[i].supportedBy.size() == 1)
			safe[*settled[i].supportedBy.cbegin()] = 0;

    int ans = 0;

	for(int i=0; i<settled.size(); i++)
	{
		set<int> falling = {i}, toEvaluate = settled[i].supports;
		int toRemove = -1;
		while (true)
		{
			for(int j:toEvaluate)
            {
                int count = count_if(settled[j].supportedBy.cbegin(), settled[j].supportedBy.cend(), [&falling](int a) 
                { return falling.find(a) != falling.cend(); });
				if(count == settled[j].supportedBy.size())
                {
                    toRemove = j;
                    break;
                }
            }

			if(toRemove >= 0)
			{
				toEvaluate.erase(toRemove);
				falling.insert(toRemove);
				for(int j:settled[toRemove].supports)
					toEvaluate.insert(j);
				toRemove = -1;
			}
			else 
                break;
		}
		ans += falling.size()-1;
	}

    cout<<ans;
    inputFile.close();
    return 0;
}