#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

#define ll long long

using namespace std;

const int maxn=1e6+10;

struct node{
    int l,r;
    ll v;
}t[maxn<<5];

int root[maxn],cnt=0,p=0,n,m;

void build(int &x,int l,int r)
{
    t[++cnt]=t[x];
    x=cnt;

    if(l==r)
    {
        cin>>t[x].v;
        return;
    }

    int mid=l+r>>1;

    build(t[x].l,l,mid);
    build(t[x].r,mid+1,r);
}


void modify(int &x,int l,int r,int dist,ll v)
{
    t[++cnt]=t[x];
    x=cnt;

    if(l==r)
    {
        t[x].v=v;
        return;
    }

    int mid=l+r>>1;

    if(mid>=dist)modify(t[x].l,l,mid,dist,v);
    else modify(t[x].r,mid+1,r,dist,v);
}

ll query(int x,int l,int r,int dist)
{
    if(l==r)return t[x].v;

    int mid=l+r>>1;

    if(mid>=dist)return query(t[x].l,l,mid,dist);
    else return query(t[x].r,mid+1,r,dist);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin>>n>>m;

    build(root[0],1,n);

    while(m--)
    {
        int x,op,y;

        cin>>x>>op>>y;

        if(op==1)
        {
            ll v;
            cin>>v;

            root[++p]=root[x];

            modify(root[p],1,n,y,v);
        }
        else
        {
            root[++p]=root[x];
            cout<<query(root[p],1,n,y)<<'\n';
        }
    }

    cout<<endl;
    system("pause");
    return 0;
}
