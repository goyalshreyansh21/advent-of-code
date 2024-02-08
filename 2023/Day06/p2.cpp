#include <iostream>
using namespace std;

int main()
{
    long long t, d;
    cin>>t>>d;
    long long l = 1, r = t-1;
    while(l<r)
    {
        long long mid = r - (r-l)/2;
        long long tleft = t-mid;
        if(mid*tleft > d)
            l = mid;
        else
            r = mid-1;
    }

    cout<<2*l - t +1;
    return 0;
}