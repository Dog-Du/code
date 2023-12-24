#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

#define ll long long
using namespace std;

const int maxn=1e5+10;

struct node{
    ll lz,v;
}t[maxn<<2];

void pushup(int x)
{
    t[x].v=t[x<<1].v+t[x<<1|1].v;
}

void pushdown(int x,int l,int r)
{
    if(t[x].lz==0)return;
    int mid=l+r>>1;

    t[x<<1].v+=t[x].lz*(mid-l+1);
    t[x<<1|1].v+=t[x].lz*(r-mid);
    t[x<<1].lz+=t[x].lz;
    t[x<<1|1].lz+=t[x].lz;

    t[x].lz=0;
}

void build(int x,int l,int r)
{
    if(l==r)
    {
        cin>>t[x].v;
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
        t[x].lz+=k;
        t[x].v+=k*(r-l+1);
        return;
    }

    int mid=l+r>>1;

    pushdown(x,l,r);

    if(mid>=L)modify(x<<1,l,mid,L,R,k);
    if(mid<R)modify(x<<1|1,mid+1,r,L,R,k);

    pushup(x);
}

ll query(int x,int l,int r,int L,int R)
{
    if(l>=L&&r<=R)
    {
        return t[x].v;
    }

    pushdown(x,l,r);

    ll ans=0;
    int mid=l+r>>1;

    if(mid>=L)ans+=query(x<<1,l,mid,L,R);
    if(mid<R)ans+=query(x<<1|1,mid+1,r,L,R);

    return ans;
}

int n,m;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    
    cin>>n>>m;

    build(1,1,n);

    while(m--)
    {
        int op;

        cin>>op;

        if(op==1)
        {
            int x,y,k;
            cin>>x>>y>>k;
            modify(1,1,n,x,y,k);
        }
        else{
            int x,y;
            cin>>x>>y;
            cout<<query(1,1,n,x,y)<<'\n';
        }
    }
    
    cout<<endl;
    system("pause");
    return 0;
}
