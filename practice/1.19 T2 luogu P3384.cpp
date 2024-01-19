#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn=1e5+10;

vector<int> graph[maxn];

int n,m,root,MOD,tim=0;
int w[maxn],weight[maxn],depth[maxn],son[maxn],fa[maxn],siz[maxn],top[maxn],dfn[maxn];

pair<int,int> tree[maxn<<2];

void pushup(int x,int l,int r)
{
    tree[x].first=(tree[x<<1].first+tree[x<<1|1].first)%MOD;
}

void pushdown(int x,int l,int r)
{
    int mid=l+r>>1;
    tree[x<<1].first+=tree[x].second*(mid-l+1)%MOD;
    tree[x<<1|1].first+=tree[x].second*(r-mid)%MOD;

    tree[x<<1].second+=tree[x].second;
    tree[x<<1|1].second+=tree[x].second;

    tree[x].second=0;
}

void build(int x,int l,int r)
{
    tree[x].second=0;
    if(l==r)
    {
        tree[x].first=weight[l];
        return;
    }

    int mid=l+r>>1;

    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);

    pushup(x,l,r);
}

void modify(int L,int R,int k,int x=1,int l=1,int r=n)
{
    if(l>=L&&r<=R)
    {
        tree[x].first+=(r-l+1)*k;
        tree[x].second+=k;
        return;
    }

    int mid=l+r>>1;
    pushdown(x,l,r);

    if(mid>=L)modify(L,R,k,x<<1,l,mid);
    if(mid<R)modify(L,R,k,x<<1|1,mid+1,r);

    pushup(x,l,r);
}

int query(int L,int R,int x=1,int l=1,int r=n)
{
    if(l>=L&&r<=R)
        return tree[x].first;
    
    int ans=0,mid=l+r>>1;

    pushdown(x,l,r);
    
    if(mid>=L)
        ans=(ans+query(L,R,x<<1,l,mid))%MOD;
    
    if(mid<R)
        ans=(ans+query(L,R,x<<1|1,mid+1,r))%MOD;
    
    return ans;
}

void dfs1(int now,int f)
{
    siz[now]=1;
    depth[now]=depth[f]+1;
    fa[now]=f;

    int maxsize=-1;

    for(const auto&it:graph[now])
    {
        if(it==f)continue;
        dfs1(it,now);

        siz[now]+=siz[it];

        if(siz[it]>maxsize)
        {
            maxsize=siz[it];
            son[now]=it;
        }
    }
}

void dfs2(int now,int t)
{
    top[now]=t;
    dfn[now]=++tim;
    weight[tim]=w[now];

    if(son[now]==0)
        return;
    
    dfs2(son[now],t);

    for(const auto&it : graph[now])
    {
        if(it==fa[now]||it==son[now])continue;
        dfs2(it,it);
    }

}

void modifytree(int x,int k)
{
    modify(dfn[x],dfn[x]+siz[x]-1,k);
}

void modifychain(int x,int y,int k)
{
    while(top[x]!=top[y])
    {
        if(depth[top[x]]<depth[top[y]])
            swap(x,y);
        
        modify(dfn[top[x]],dfn[x],k);
        x=fa[top[x]];
    }

    if(dfn[x]>dfn[y])
        swap(x,y);

    modify(dfn[x],dfn[y],k);
}

int querytree(int x)
{
    return query(dfn[x],dfn[x]+siz[x]-1)%MOD;
}


int querychain(int x,int y)
{
    int ans=0;

    while(top[x]!=top[y])
    {
        if(depth[top[x]]<depth[top[y]])
            swap(x,y);
        
        ans=(ans+query(dfn[top[x]],dfn[x]))%MOD;
        x=fa[top[x]];
    }

    if(dfn[x]>dfn[y])
        swap(x,y);

    return (ans+query(dfn[x],dfn[y]))%MOD;
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

    cin>>n>>m>>root>>MOD;

    for(int i=1;i<=n;++i)
        cin>>w[i];
    
    for(int i=1,x,y;i<n;++i)
    {
        cin>>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }


    dfs1(root,root);
    dfs2(root,root);

    build(1,1,n);

    int op,x,y,k;
    while(m--)
    {
        cin>>op>>x;

        if(op==1)
        {
            cin>>y>>k;
            modifychain(x,y,k);
        }
        else if(op==2)
        {
            cin>>y;
            cout<<querychain(x,y)<<'\n';
        }
        else if(op==3)
        {
            cin>>k;
            modifytree(x,k);
        }
        else if(op==4)
        {
            cout<<querytree(x)<<'\n';
        }
    }
//-------------------------------------------------

#ifdef LOCAL
    cout << "\nTime Used: \n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
