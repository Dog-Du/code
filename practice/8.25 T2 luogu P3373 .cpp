#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

#define ll long long

using namespace std;

const int maxn=1e5+10;

struct node{
    ll v,plz,mlz;
}t[maxn<<2];

int n,q;
ll mod=571373;

void pushup(node&x,node&l,node&r)
{
    x.v=l.v+r.v;
}

void pushdown(int x,int l,int r)
{
    int mid=l+r>>1;
    t[x<<1].v=(t[x<<1].v*t[x].mlz+(mid-l+1)*t[x].plz)%mod;
    t[x<<1|1].v=(t[x<<1|1].v*t[x].mlz+(r-mid)*t[x].plz)%mod;
    t[x<<1].mlz=t[x].mlz*t[x<<1].mlz%mod;
    t[x<<1|1].mlz=t[x].mlz*t[x<<1|1].mlz%mod;
    t[x<<1].plz=(t[x<<1].plz*t[x].mlz+t[x].plz)%mod;
    t[x<<1|1].plz=(t[x].plz+t[x<<1|1].plz*t[x].mlz)%mod;
    t[x].plz=0;
    t[x].mlz=1;
}

void build(int x,int l,int r)
{
    t[x].mlz=1,t[x].plz=0;

    if(l==r)
    {
        cin>>t[x].v;
        return;
    }

    int mid=l+r>>1;

    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);

    pushup(t[x],t[x<<1],t[x<<1|1]);
}

void mmodify(int x,int l,int r,int L,int R,ll k)
{
    if(l>=L&&r<=R)
    {
        t[x].mlz*=k;
        t[x].plz*=k;
        t[x].v*=k;
        return;
    }

    int mid=l+r>>1;
    pushdown(x,l,r);

    if(mid>=L)mmodify(x<<1,l,mid,L,R,k);
    if(mid<R)mmodify(x<<1|1,mid+1,r,L,R,k);

    pushup(t[x],t[x<<1],t[x<<1|1]);
}


void pmodify(int x,int l,int r,int L,int R,ll k)
{
    if(l>=L&&r<=R)
    {
        t[x].plz+=k;
        t[x].v+=(r-l+1)*k;
        return;
    }

    int mid=l+r>>1;

    pushdown(x,l,r);

    if(mid>=L)pmodify(x<<1,l,mid,L,R,k);
    if(mid<R)pmodify(x<<1|1,mid+1,r,L,R,k);

    pushup(t[x],t[x<<1],t[x<<1|1]);
}

ll query(int x,int l,int r,int L,int R)
{
    if(l>=L&&r<=R)return t[x].v;

    int mid=l+r>>1;

    pushdown(x,l,r);

    ll ans=0;

    if(mid>=L)ans+=query(x<<1,l,mid,L,R);
    if(mid<R)ans+=query(x<<1|1,mid+1,r,L,R);

    return ans%mod;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin>>n>>q>>mod;

    build(1,1,n);

    while(q--)
    {
        int op,l,r;
        cin>>op>>l>>r;

        if(op==1)
        {
            int k;
            cin>>k;
            mmodify(1,1,n,l,r,k);
        }
        else if(op==2)
        {
            int k;
            cin>>k;
            pmodify(1,1,n,l,r,k);
        }
        else{
            cout<<query(1,1,n,l,r)<<'\n';
        }
    }

    cout<<endl;
    system("pause");
    return 0;
}
