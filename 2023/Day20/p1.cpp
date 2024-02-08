#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

class FlipFlop
{
public:
    int state;
    vector<string> dest;
    FlipFlop() {}
    FlipFlop(vector<string> v)
    {
        state = 0;
        dest = v;
    }
};

class Conjunctor
{
public:
    unordered_map<string,int> memory;
    vector<string> dest;
    Conjunctor() {}
    Conjunctor(vector<string> v)
    {
        dest = v;
    }
};

int main() 
{
    ifstream inputFile("text.txt");
    string line;

    unordered_map<string,FlipFlop> ff;
    unordered_map<string,Conjunctor> cj;
    unordered_set<string> ffs, cjs;

    queue<pair<string,int>> startq;
    
    getline(inputFile, line);

    string start = line.substr(line.find(' ')+4);
    int startPos = 0;
    while(1) 
    {
        int commaPos = start.find(',', startPos);
        if(commaPos == string::npos) 
        {
            startq.push({start.substr(startPos),0});
            break;
        }
        startq.push({start.substr(startPos,commaPos- startPos),0});
        startPos = commaPos + 2;
    }

    while(getline(inputFile,line))
    {
        string source = line.substr(0,line.find(' '));
        string destination = line.substr(line.find(' ')+4);
        vector<string> tokens;

        int startPos = 0;
        while(1) 
        {
            int commaPos = destination.find(',', startPos);
            if(commaPos == string::npos) 
            {
                tokens.push_back(destination.substr(startPos));
                break;
            }
            tokens.push_back(destination.substr(startPos,commaPos-startPos));
            startPos = commaPos + 2;
        }
        
        if(source[0]=='%')
        {
            ff.insert({source.substr(1),FlipFlop(tokens)});
            ffs.insert(source.substr(1));
        }
        else
        {
            cj.insert({source.substr(1),Conjunctor(tokens)});
            cjs.insert(source.substr(1));
        }
    }

    int s=startq.size();
    while(s)
    {
        if(cjs.find(startq.front().first)!=cjs.end())
            cj[startq.front().first].memory.insert({"broadcast",0});
        startq.push(startq.front());
        startq.pop();
        s--;
    }

    for(string flipflop:ffs)
    {
        for(string s:ff[flipflop].dest)
        {
            if(cjs.find(s)!=cjs.end())
                cj[s].memory[flipflop] = 0;
        }
    }

    for(string conjunctor:cjs)
    {
        for(string s:cj[conjunctor].dest)
        {
            if(cjs.find(s)!=cjs.end())
                cj[s].memory[conjunctor] = 0;
        }
    }

    int low = 1000, high = 0;

    for(int i=0; i<1000; i++)
    {
        queue<pair<string,int>> q = startq;
        while(!q.empty())
        {
            string curr = q.front().first;
            int signal = q.front().second;
            
            if(signal)
                high++;
            else
                low++;

            q.pop();

            if(cj.find(curr)!=cj.end())
            {
                int signals = 0;
                for(pair<string,int> p:cj[curr].memory)
                    signals += p.second;
                
                int newsignal = signals==cj[curr].memory.size() ? 0 : 1;
                for(string s:cj[curr].dest)
                {
                    if(cjs.find(s)!=cjs.end())
                        cj[s].memory[curr] = newsignal;
                    q.push({s,newsignal});
                }
            }
            else
            {
                if(signal)
                    continue;
                
                ff[curr].state = ff[curr].state ? 0 : 1;
                int newsignal = ff[curr].state;
                for(string s:ff[curr].dest)
                {
                    if(cjs.find(s)!=cjs.end())
                        cj[s].memory[curr] = newsignal;
                    q.push({s,newsignal});
                }
            }
        }
    }

    cout<<high*low;
    inputFile.close();
    return 0;
}