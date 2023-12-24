using namespace std;
#include<iostream>
#define ll long long
#include<algorithm>

const int maxn=2e5+10;

struct node{
    int l,r;
    int cnt;
}t[maxn<<5];

int n,m,tot;
int root[maxn],cnt=0;
ll a[maxn],b[maxn];

void modify(int &x,int l,int r,int &p)
{
    t[++cnt]=t[x];
    x=cnt;
    t[x].cnt++;

    if(l==r)return;

    int mid=l+r>>1;

    if(mid>=p)modify(t[x].l,l,mid,p);
    else modify(t[x].r,mid+1,r,p);
}

int query(int L,int R,int l,int r,int k)
{
    if(l==r)return l;

    int x=t[t[R].l].cnt-t[t[L].l].cnt;

    int mid=l+r>>1;

    if(x>=k)return query(t[L].l,t[R].l,l,mid,k);
    else return query(t[L].r,t[R].r,mid+1,r,k-x);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    
    cin>>n>>m;

    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
        b[i]=a[i];
    }

    sort(b+1,b+1+n);

    tot=unique(b+1,b+1+n)-b-1;

    for(int i=1,id;i<=n;++i)
    {
        id=lower_bound(b+1,b+1+tot,a[i])-b;
        root[i]=root[i-1];
        modify(root[i],1,tot,id);
    }

    int l,r,k,t;

    while(m--)
    {
        cin>>l>>r>>k;

        t=query(root[l-1],root[r],1,tot,k);
        cout<<b[t]<<endl;
        
    }
    return 0;
}
