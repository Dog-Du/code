#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

#define ll long long

using namespace std;

const int maxn=1e2+10;

int add[maxn][maxn];
int n,m;

bool check(int x)
{

    for(int i=1;i+x<=n;++i)
        for(int j=1;j+x<=m;++j)
            if((add[i+x][j+x]-add[i-1][j+x]-add[i+x][j-1]+add[i-1][j-1])==0)
                return true;

    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin>>n>>m;

    for(int i=1,t;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            cin>>t;

            add[i][j]=add[i-1][j]+add[i][j-1]-add[i-1][j-1];

            if(!t)  
                add[i][j]++;
        }
 
    }

    int l=1,r=min(n,m),mid,ans=0;

    while(l<=r)
    {
        mid=l+r>>1;

        if(check(mid-1))
            l=mid+1,ans=max(ans,mid);
        else
            r=mid-1;
    }

    cout<<ans;

    cout<<endl;
    system("pause");
    return 0;
}
