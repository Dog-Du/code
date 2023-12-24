#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

using namespace std;

const int maxn=2e5+10;

struct EDGE{
    int next,to,weigh,from;
} edge[maxn<<1],e[maxn<<1];

int n,m,q,cnt=1,head[maxn],used[maxn],pre[maxn],depth[maxn],dp[maxn][25],weigh[maxn][25];

int find(int x)
{
    return x==pre[x]?x:pre[x]=find(pre[x]);
}

void Union(int x,int y)
{
    x=find(x);
    y=find(y);

    if(x==y)return;

    pre[x]=y;
}

void add(int x,int y,int w)
{
    edge[cnt]={head[x],y,w};
    head[x]=cnt++;
}

void prepare()
{
    for(int i=1;i<=n;++i)pre[i]=i;

    for(int i=1,x,y;i<=m;++i)
    {
        x=e[i].from;
        y=e[i].to;

        if(find(x)==find(y))continue;

        Union(x,y);

        add(x,y,e[i].weigh);
        add(y,x,e[i].weigh);
    }
}

void dfs(int x)
{
    for(int i=1;(1<<i)<depth[x];++i)
        dp[x][i]=dp[dp[x][i-1]][i-1],
        weigh[x][i]=weigh[x][i-1]^weigh[dp[x][i-1]][i-1];
    
    used[x]=1;

    for(int i=head[x],v;i;i=edge[i].next)
    {
        v=edge[i].to;

        if(used[v])continue;

        depth[v]=depth[x]+1;
        dp[v][0]=x;
        weigh[v][0]=edge[i].weigh;

        dfs(v);
    }
}

int lca(int x,int y)
{
    if(depth[x]<depth[y])swap(x,y);

    int k=log2(depth[x]-depth[y]),ans=0;

    for(int i=k;i>=0;--i)
    {
        if(depth[dp[x][i]]>=depth[y])
        {
            ans=ans^weigh[x][i];
            x=dp[x][i];
        }
    }

    if(x==y)return ans;

    k=log2(depth[x]);

    for(int i=k;i>=0;--i)
    {
        if(dp[x][i]!=dp[y][i])
        {
            ans=ans^weigh[x][i];
            ans=ans^weigh[y][i];
            x=dp[x][i];
            y=dp[y][i];
        }
    }

    return ans^weigh[x][0]^weigh[y][0];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    
    cin>>n>>m>>q;

    for(int i=1,x,y,v;i<=m;++i)
    {
        cin>>e[i].from>>e[i].to>>e[i].weigh;
    }

    prepare();

    depth[1]=1;//这个不能忘
    dfs(1);


    while(q--)
    {
        int x,y;
        cin>>x>>y;
        cout<<lca(x,y)<<'\n';
    }

    cout<<endl;
    system("pause");
    return 0;
}
