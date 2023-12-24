#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn=5e5+10;

struct EDGE{
    int next,to,from,w;
    bool operator<(const EDGE&it)const{
        return w>it.w;
    }
}e[maxn],edge[maxn+maxn/3];

int cnt=1,n,m,q,head[maxn],pre[maxn];
int used[maxn],depth[maxn],dp[maxn][26],weigh[maxn][25];

//静态邻接表
void add(int x,int y,int w)
{
    edge[cnt]={head[x],y,x,w};
    head[x]=cnt++;
}

//并查集
int find(int x)
{
    return x==pre[x]?x:pre[x]=find(pre[x]);
}


//生成树
void kr()
{
    for(int i=1;i<=m;++i)
        cin>>e[i].to>>e[i].from>>e[i].w;
    
    sort(e+1,e+1+m);

    for(int i=1;i<=n;++i)pre[i]=i;

    for(int i=1,from,to;i<=m;++i)
    {
        from=find(e[i].from);
        to=find(e[i].to);

        if(from==to)continue;

        pre[from]=to;
        add(e[i].from,e[i].to,e[i].w);
        add(e[i].to,e[i].from,e[i].w);
    }
}

//lca预处理
void dfs(int x)
{
    used[x]=1;
    for(int i=1;(1<<i)<=depth[x];++i)
        dp[x][i]=dp[dp[x][i-1]][i-1],
        weigh[x][i]=min(weigh[x][i-1],weigh[dp[x][i-1]][i-1]);
    
    for(int i=head[x],to;i;i=edge[i].next)
    {
        to=edge[i].to;

        if(used[to])continue;

        depth[to]=depth[x]+1;
        dp[to][0]=x;
        weigh[to][0]=edge[i].w;
        dfs(to);
    }
}

//lca log(n)查找
int lca(int x,int y)
{
    if(depth[x]<depth[y])swap(x,y);

    int k=log2(depth[x]-depth[y]),ans=1e9;

    for(int i=k;i>=0;--i)
        if(depth[dp[x][i]]>=depth[y])
        {
            ans=min(ans,weigh[x][i]);
            x=dp[x][i];
        }
    
    if(x==y)return ans;

    k=log2(depth[x]);
    for(int i=k;i>=0;--i)
    {
        if(dp[x][i]!=dp[y][i])
        {
            ans=min(ans,weigh[x][i]);
            ans=min(ans,weigh[y][i]);

            x=dp[x][i];
            y=dp[y][i];
        }
    }

    return min(ans,min(weigh[x][0],weigh[y][0]));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin>>n>>m>>q;

    //先求生成树
    kr();

    //对每个连通块都进行预处理
    for(int i=1;i<=n;++i)
    {
        if(used[i])continue;
        depth[i]=1;
        dfs(i);
    }

    while(q--)
    {
        int x,y;
        cin>>x>>y;

        //如果不在同一个连通块直接-1
        if(find(x)!=find(y))cout<<-1<<'\n';
        else{
            cout<<lca(x,y)<<'\n';
        }
    }

    cout<<endl;
    system("pause");
    return 0;
}
