#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include<algorithm>

#define ll long long

using namespace std;

const int maxn=2e5+10;

double a[maxn],b[maxn];

void solve()
{
    int n;
    ll ans=0;

    cin>>n;


    for(int i=1;i<=n;++i)cin>>a[i];

    for(int i=1;i<=n;++i)
    {
        cin>>b[i];

        a[i]/=b[i];
    }

    sort(a+1,a+1+n);

    for(int i=1,l,r,mid,t1,t2;i<=n;++i)   
    {

        l=i+1,r=n,t1=0,t2=0;

        while(l<=r)
        {
            mid=l+r>>1;

            if(a[i]*a[mid]>1)
                r=mid-1;
            else    
                l=mid+1,t1=mid;
        }

        l=i+1,r=n;

        while(l<=r)
        {
            mid=l+r>>1;

            if(a[i]*a[mid]<1)
                l=mid+1;
            else    
                r=mid-1,t2=mid;
        }

        if(a[t1]==a[t2]&&a[i]*a[t1]==1)
            ans+=t1-t2+1;
    }

    cout<<ans<<endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    
    int t;
    cin>>t;

    while(t--)
    {
        solve();
    }

    return 0;
}
