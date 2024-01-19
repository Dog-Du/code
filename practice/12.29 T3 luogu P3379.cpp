#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn=5e5+10;
vector<int> tree[maxn];
int n,m,root;
int cnt=0,dfn[maxn],st[maxn][20];
//st存最小的dfn对应的节点

int get(int x,int y)
{
    return dfn[x]<dfn[y]?x:y;
}

void dfs(int now,int fa)
{
    st[dfn[now]==++cnt][0]=fa;

    for(auto&it:tree[now])
        if(it!=fa) dfs(it,now);
}

int lca(int x,int y)
{
    if(x==y)return x;
    if((x=dfn[x])>(y=dfn[y]))swap(x,y);
    int d=__lg(y-x++);
    return get(st[x][d],st[y-(1<<d)+1][d]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin>>n>>m>>root;

    for(int i=1,x,y;i<n;++i)
    {
        cin>>x>>y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    for(int i=1,t=__)

    cout<<endl;
    system("pause");
    return 0;
}
