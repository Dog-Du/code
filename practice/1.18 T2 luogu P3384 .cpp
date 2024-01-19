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
int n,m,root,MOD;

int tim=0,dfn[maxn],siz[maxn],son[maxn],fa[maxn],top[maxn],
    depth[maxn],w[maxn],val[maxn];

vector<int> graph[maxn];

struct NODE{
    int sum,lz;
}node[maxn<<2];

void dfs1(int now,int f)
{
    fa[now]=f;
    siz[now]=1;
    depth[now]=depth[f]+1;

    int maxsize=-1;

    for(const auto&it : graph[now])
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
    dfn[now]=++tim;
    w[tim]=val[now];
    top[now]=t;

    if(son[now]==0)
        return;

    dfs2(son[now],t);

    for(const auto&it : graph[now])
    {
        if(it==son[now] || 
            it==fa[now])
                continue;
        
        dfs2(it,it);
    }
}

void pushup(int now,int l,int r)
{
    node[now].sum=(node[now<<1].sum+node[now<<1|1].sum)%MOD;
}

void pushdown(int now,int l,int r)
{
    int mid=l+r>>1;
    node[now<<1].sum+=(mid-l+1)*node[now].lz%MOD;
    node[now<<1|1].sum+=(r-mid)*node[now].lz%MOD;

    node[now<<1].lz+=node[now].lz;
    node[now<<1|1].lz+=node[now].lz;

    node[now].lz=0;
}


void build(int now,int l,int r)
{
    node[now].lz=0;
    if(l==r)
    {
        node[now].sum=w[l];
        return;
    }

    int mid=l+r>>1;

    build(now<<1,l,mid);
    build(now<<1|1,mid+1,r);

    pushup(now,l,r);
}


void modify(int L,int R,int k,int now=1,int l=1,int r=n)
{
    if(l>=L&&r<=R)
    {
       node[now].lz+=k;
       node[now].sum+=(r-l+1)*k;
       return;
    }

    int mid=l+r>>1;
    pushdown(now,l,r);

    if(mid>=L)modify(L,R,k,now<<1,l,mid);
    if(mid<R)modify(L,R,k,now<<1|1,mid+1,r);

    pushup(now,l,r);
}

int query(int L,int R,int now=1,int l=1,int r=n)
{
    if(l>=L&&r<=R)
        return node[now].sum;
    
    int mid=l+r>>1,ans=0;

    pushdown(now,l,r);

    if(mid>=L)
        ans=(ans+query(L,R,now<<1,l,mid))%MOD;
    
    if(mid<R)
        ans=(ans+query(L,R,now<<1|1,mid+1,r))%MOD;

    return ans;
}


void modifychain(int x,int y,int k)
{
    k%=MOD;

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
    
    ans=(ans+query(dfn[x],dfn[y]))%MOD;
    
    return ans;
}

void modifytree(int x,int k)
{
    modify(dfn[x],dfn[x]+siz[x]-1,k);
}

int querytree(int x)
{
    return query(dfn[x],dfn[x]+siz[x]-1);
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
        cin>>val[i];
    
    for(int i=1,x,y;i<n;++i)
    {
        cin>>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs1(root,root);
    dfs2(root,root);
    build(1,1,n);

    int op,x,y,z;

    while(m--)
    {
        cin>>op>>x;

        if(op==1)
        {
            cin>>y>>z;
            modifychain(x,y,z);
        }
        else if(op==2)
        {
            cin>>y;
            cout<< querychain(x,y)%MOD << '\n';
        }
        else if(op==3)
        {
            cin>>z;
            modifytree(x,z);
        }
        else if(op==4)
        {
            cout<< querytree(x)%MOD << '\n';
        }

    }

//-------------------------------------------------

#ifdef LOCAL
    cout << "Time Used:\n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
