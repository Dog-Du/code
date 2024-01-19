#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn=500000+10;

vector<int> graph[maxn];
int n,m,root,tim=0;
int dfn[maxn],top[maxn],fa[maxn],son[maxn],node_count[maxn],depth[maxn];

void dfs1(int now,int f)
{
    depth[now]=depth[f]+1;
    fa[now]=f;
    node_count[now]=1;

    int maxsize=-1;

    for(const auto&it : graph[now])
    {
        if(it==f)continue;
        dfs1(it,now);

        node_count[now]+=node_count[it];

        if(node_count[it]>maxsize)
        {
            son[now]=it;
            maxsize=node_count[it];
        }
    }
}

void dfs2(int now,int t)
{
    dfn[now]=++tim;
    top[now]=t;

    if(son[now]==0)
        return;

    dfs2(son[now],t);

    for(const auto&it : graph[now])
    {
        if(it==fa[now]||it==son[now])
            continue;
        
        dfs2(it,it);
    }
}

int lca(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(depth[top[x]]<depth[top[y]])
            swap(x,y);
        
        x=fa[top[x]];
    }

    return depth[x]<depth[y]?x:y;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

#ifdef LOCAL
    clock_t c1 = clock();
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif

//-------------------------------------------------

    cin>>n>>m>>root;

    for(int i=1,x,y;i<n;++i)
    {
        cin>>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    
    dfs1(root,root);
    dfs2(root,root);
    int x,y;
    while(m--)
    {
        cin>>x>>y;
        cout<<lca(x,y)<<'\n';
    }

//-------------------------------------------------

#ifdef LOCAL
    cout << "Time Used: " << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
