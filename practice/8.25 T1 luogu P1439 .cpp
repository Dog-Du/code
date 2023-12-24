#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

#define ll long long

using namespace std;

const int maxn=1e5+10;

int a[maxn],b[maxn],inx[maxn];

int n,p=0;


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    
    cin>>n;

    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
        inx[a[i]]=i;
    }

    for(int i=1;i<=n;++i)
    {
        cin>>b[i];
        b[i]=inx[b[i]];
    }

    for(int i=1,l,r,mid,t;i<=n;++i)
    {
        if(p==0||b[i]>a[p])
        {
            a[++p]=b[i];
            continue;
        }

        l=1,r=p,t=-1;

        while(l<=r)
        {
            mid=l+r>>1;

            if(a[mid]>=b[i])
            {
                r=mid-1;
                t=mid;
            }
            else
                l=mid+1;
        }

        if(t!=-1)a[t]=b[i];
    }

    cout<<p<<endl;
    
    cout<<endl;
    system("pause");
    return 0;
}
