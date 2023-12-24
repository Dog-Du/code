using namespace std;
#include<iostream>
#define ll long long
#include<algorithm>

const int maxn=1e6+10;

struct node{
    int l,r;
    ll v;
}t[maxn<<5];

int n,m,tot,cnt=0,p=0;
int root[maxn];

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

void modify(int &x,int l,int r,int & dist,ll &v)
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

ll query(int x,int l,int r,int& dist)
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

    int x,y,op;
    ll v;

    while(m--)
    {
        cin>>y>>op;

        if(op==1)
        {
            cin>>x>>v;

            root[++p]=root[y];
            
            modify(root[p],1,n,x,v);
        }
        else
        {
            cin>>x;

            root[++p]=root[y];

            cout<<query(root[y],1,n,x)<<'\n';
        }
    }
    return 0;
}
