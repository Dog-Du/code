#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn=5e2+10;
ll line[maxn][maxn];//第i列前j行
int n,m;
ll k,ans=0;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin>>n>>m>>k;
             
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            cin>>line[j][i];
            line[j][i]+=line[j][i-1];
        }
    }

    for(int down=1;down<=n;++down)
    {
        for(int up=down;up<=n;++up)
        {
            ll sum=0;
            int l=1,r=1;

            for(;r<=m;++r)
            {
                sum+=line[r][up]-line[r][down-1];
                while(sum>k)
                {
                    sum-=line[l][up]-line[l++][down-1];
                }
                ans+=r-l+1;
            }
        }
    }

    cout<<ans<<endl;

    cout<<endl;
    system("pause");
    return 0;
}