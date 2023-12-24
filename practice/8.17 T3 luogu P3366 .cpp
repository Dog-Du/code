#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn=2e5+10;

struct EDGE{
    int to,from,w;

    bool operator<(const EDGE&it)
    {
        return w<it.w;
    }
}edge[maxn];

int n,m;

int pre[maxn];

int find(int x)
{
    return x==pre[x]?x:pre[x]=find(pre[x]);
}

void kr()
{
    for(int i=1;i<=n;++i)pre[i]=i;

    sort(edge+1,edge+1+m);

    int cnt=0,ans=0;

    for(int i=1,x,y;i<=m;++i)
    {
        x=find(edge[i].from);
        y=find(edge[i].to);

        if(x==y)continue;

        pre[x]=y;
        ans+=edge[i].w;
        ++cnt;
    }

    if(cnt==n-1)cout<<ans;
    else cout<<"orz";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    
    cin>>n>>m;

    for(int i=1;i<=m;++i)
        cin>>edge[i].from>>edge[i].to>>edge[i].w;

    kr();

    cout<<endl;
    system("pause");
    return 0;
}
