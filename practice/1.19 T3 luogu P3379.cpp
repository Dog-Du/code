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
int n,m,root;
int son[maxn],depth[maxn],fa[maxn],top[maxn];

int dfs1(int now,int f)
{
    depth[now]=depth[f]+1;
    fa[now]=f;

    int maxsize=-1,cur=0,node_count=1;

    for(const auto&it : graph[now])
    {
        if(it==f)continue;

        cur=dfs1(it,now);
        node_count+=cur;

        if(cur>maxsize)
        {
            maxsize=cur;
            son[now]=it;
        }
    }
    return node_count;
}

void dfs2(int now,int t)
{
    top[now]=t;

    if(son[now]==0)
        return;
    
    dfs2(son[now],t);

    for(const auto&it : graph[now])
    {
        if(it==son[now]||it==fa[now])
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
//------------- ------------------------------------

#ifdef LOCAL
    cout << "\nTime Used: \n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
