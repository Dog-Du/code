#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

#define ll long long

using namespace std;

const int maxn=1e5+10;

int a[maxn],dp[maxn],t[maxn<<2],pre[maxn];
int n,q;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin>>n>>q;

    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
        
        dp[i]=max(dp[i-1],pre[a[i]]);

        pre[a[i]]=i;
    }

    while(q--)
    {
        int l,r;

        cin>>l>>r;

        if(dp[r]>=l)cout<<"No\n";
        else cout<<"Yes\n";
    }

    cout<<endl;
    system("pause");
    return 0;
}
