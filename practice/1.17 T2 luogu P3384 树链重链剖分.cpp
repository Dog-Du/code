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

vector<int> graph[maxn];//邻接表

struct NODE{
    int fa,son,node_count,depth;
    int dfn,top,w;
}node[maxn];

//first是和，second是lazy tag
pair<int,int> tree[maxn<<2];

int n,m,root,mod,tim,weight[maxn];

//第一次填上 depth，fa和node_count并找到重儿子
void dfs1(int now,int fa)
{
    node[now].fa=fa;
    node[now].depth=node[fa].depth+1;
    node[now].node_count=1;

    int maxsize=-1;

    for(const auto&it:graph[now])
    {
        if(it==fa)continue;
        dfs1(it,now);

        node[now].node_count+=node[it].node_count;

        if(node[it].node_count>maxsize)
        {
            maxsize=node[it].node_count;
            node[now].son=it;
        }
    }
}

//t表示top，
void dfs2(int now,int t)
{
    node[now].dfn=++tim;
    node[now].top=t;
    weight[tim]=node[now].w;

    //如果没有重儿子，说明到叶子结点了，返回
    if(node[now].son==0)return;

    //先走重儿子
    dfs2(node[now].son,t);

    //下面走轻儿子 
    for(const auto&it:graph[now])
    {
        if(it==node[now].son||
            it==node[now].fa)
            continue;
        
        //路线的第一个为轻儿子
        dfs2(it,it);
    }
}

void pushup(pair<int,int>&x,pair<int,int>&l,pair<int,int>&r)
{
    x.first=(l.first+r.first)%mod;
}

void pushdown(int now,int l,int r)
{
    int mid=l+r>>1;

    tree[now<<1].second+=tree[now].second;
    tree[now<<1|1].second+=tree[now].second;

    tree[now<<1].first+=(mid-l+1)*tree[now].second%mod;
    tree[now<<1|1].first+=(r-mid)*tree[now].second%mod;

    tree[now].second=0;
}

void build(int now,int l,int r)
{
    tree[now].second=0;
    if(l==r)
    {
        tree[now].first=weight[l];
        return;
    }

    int mid=l+r>>1;
    build(now<<1,l,mid);
    build(now<<1|1,mid+1,r);
    pushup(tree[now],tree[now<<1],tree[now<<1|1]);
}

int query(int now,int l,int r,int L,int R)
{
    if(l>=L&&r<=R)
        return tree[now].first;

    int mid=l+r>>1,ans=0;

    pushdown(now,l,r);

    if(mid>=L)
        ans=(ans+query(now<<1,l,mid,L,R))%mod;
    
    if(mid<R)
        ans=(ans+query(now<<1|1,mid+1,r,L,R))%mod;
    
    return ans;
}

void modify(int now,int l,int r,int L,int R,int k)
{
    if(l>=L&&r<=R)
    {
        tree[now].first+=(r-l+1)*k;
        tree[now].second+=k;
        return;
    }

    int mid=l+r>>1;
    pushdown(now,l,r);

    if(mid>=L)
        modify(now<<1,l,mid,L,R,k);
    if(mid<R)
        modify(now<<1|1,mid+1,r,L,R,k);

    pushup(tree[now],tree[now<<1],tree[now<<1|1]);
}

void modifytree(int now,int k)
{
    modify(1,1,n,node[now].dfn,
        node[now].dfn+node[now].node_count-1,k);
}

int querytree(int now)
{
    return query(1,1,n,node[now].dfn,
        node[now].dfn+node[now].node_count-1);
}

void modifychain(int x,int y,int k)
{
    k%=mod;

    while(node[x].top!=node[y].top)
    {
        if(node[node[x].top].depth<
            node[node[y].top].depth)
            swap(x,y);
        
        //这里是 dfn[top[x]] ，弄错了一次，怎么找都没找到。一直错。
        modify(1,1,n,node[node[x].top].dfn,node[x].dfn,k);
        x=node[node[x].top].fa;
    }

    if(node[x].dfn>node[y].dfn)
        swap(x,y);
    
    modify(1,1,n,node[x].dfn,node[y].dfn,k);
}

int querychain(int x,int y)
{
    int ans=0;

    while(node[x].top!=node[y].top)
    {
        if(node[node[x].top].depth<
            node[node[y].top].depth)
            swap(x,y);
        
        ans=(ans+query(1,1,n,node[node[x].top].dfn,node[x].dfn))%mod;
        x=node[node[x].top].fa;
    }

    if(node[x].dfn>node[y].dfn)
        swap(x,y);
    
    ans=(ans+query(1,1,n,node[x].dfn,node[y].dfn))%mod;
    return ans;
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

    cin>>n>>m>>root>>mod;

    for(int i=1;i<=n;++i)
        cin>>node[i].w;
    

    for(int i=1,x,y;i<n;++i)
    {
        cin>>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs1(root,root);
    dfs2(root,root);

    build(1,1,n);

    int x,y,z,op;

    while(m--)
    {
        cin>>op>>x;

        if(op==4)
        {
            cout<<querytree(x)%mod<<'\n';
            continue;
        }
        cin>>y;

        if(op==3)
        {
            modifytree(x,y);
            continue;
        }
        else if(op==2)
        {
            cout<<querychain(x,y)%mod<<'\n';
            continue;
        }

        cin>>z;

        modifychain(x,y,z);
    }

//-------------------------------------------------

#ifdef LOCAL
    cout << "Time Used:\n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
