#include <iostream>
using namespace std;

int main()
{
    long long ans = 1;
    for(int i=0; i<4; i++)
    {
        int t, d;
        cin>>t>>d;

        int l = 1, r = t-1;
        while(l<r)
        {
            int mid = r - (r-l)/2;
            int tleft = t-mid;
            if(mid*tleft > d)
                l = mid;
            else
                r = mid-1;
        }

        ans *= (2*l - t +1);
    }
    cout<<ans;
    return 0;
}