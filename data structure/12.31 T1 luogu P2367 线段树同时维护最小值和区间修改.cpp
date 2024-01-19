#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

struct node{
    int first,second;//first表示最小值，second表示懒标记
};

const int maxn=5e6;
node tree[maxn<<2];

void pushup(int x)
{
    tree[x].first=min(tree[x<<1].first,tree[x<<1|1].first);
}

void pushdown(int x)//对一个区间整体加k，那么最小值也要加k
{
    tree[x<<1].first+=tree[x].second;
    tree[x<<1|1].first+=tree[x].second;

    tree[x<<1].second+=tree[x].second;
    tree[x<<1|1].second+=tree[x].second;

    tree[x].second=0;
}

void build(int x,int l,int r)
{
    tree[x].second=0;
    if(l==r)
    {
        cin>>tree[x].first;
        return;
    }
    int mid=l+r>>1;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    pushup(x);
}

void modify(int x,int l,int r,int L,int R,int k)
{
    if(l>=L&&r<=R)
    {
        tree[x].second+=k;//打标记
        tree[x].first+=k;//保证first一直是修改之后的最小值
        return;
    }

    int mid=l+r>>1;
    pushdown(x);
    if(mid>=L)modify(x<<1,l,mid,L,R,k);
    if(mid<R)modify(x<<1|1,mid+1,r,L,R,k);
    pushup(x);
}

int query(int x,int l,int r,int L,int R)
{
    if(l>=L&&r<=R)return tree[x].first;
    
    int mid=l+r>>1,ans=1e9;

    pushdown(x);

    if(mid>=L)ans=min(ans,query(x<<1,l,mid,L,R));
    if(mid<R)ans=min(ans,query(x<<1|1,mid+1,r,L,R));
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    int n,m;
    cin>>n>>m;
   // tree.resize(n<<2);
    
    build(1,1,n);

    while (m--)
    {
        int x,y,z;
        cin>>x>>y>>z;
        modify(1,1,n,x,y,z);
    }
    
    cout<<query(1,1,n,1,n)<<endl;

    cout<<endl;
    system("pause");
    return 0;
}
