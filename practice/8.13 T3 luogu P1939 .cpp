#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#define ll long long

using namespace std;

ll t[10][10];
ll mod=1e9+7;

void mpower(ll a[10][10],ll b[10][10],int x,int y,int z)
{
    for(int i=1;i<=x;++i)
        for(int j=1;j<=z;++j)
            t[i][j]=0;
    
    for(int i=1;i<=x;++i)
        for(int j=1;j<=z;++j)
            for(int k=1;k<=y;++k)
                t[i][j]=(t[i][j]+(a[i][k]%mod*b[k][j]%mod)%mod)%mod;
    
    for(int i=1;i<=x;++i)
        for(int j=1;j<=z;++j)
            a[i][j]=t[i][j];
}

ll qpower(int n)
{
    n-=5;

    ll base[10][10]={0};
    
    base[1][1]=base[1][3]=base[2][1]=base[3][2]=1;

    ll ans[10][10],temp[10][10];

    temp[1][1]=temp[2][1]=temp[3][1]=1;
    ans[1][1]=ans[1][2]=ans[1][3]
    =ans[2][1]=ans[2][2]=ans[2][3]
    =ans[3][1]=ans[3][2]=ans[3][3]=1;

    while(n)
    {
        if(n%2==1)mpower(ans,base,3,3,3);
        mpower(base,base,3,3,3);
        n/=2;
    }

    mpower(ans,temp,3,3,1);

    return ans[1][1];
}

ll solve()
{
    int n;

    cin>>n;

    if(n<=5)
    {
        if(n<=3)return 1;
        else if(n==4)return 2;
        else if(n==5)return 3;
    }
    else return qpower(n);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    
    int t;
    cin>>t;

    while(t--)
    {
        cout<<solve()<<'\n';
    }

    cout<<endl;
    system("pause");
    return 0;
}
