#include <iostream>
#include <algorithm>
using namespace std;

const int maxn=2e5+10;

struct node{
    int *p,len;
}t[maxn<<2];

struct num{
    int id,val;
}b[maxn];

bool cmp(num&a,num&b)
{
    return a.val<b.val;
}

int n,m,l,r,k,tot,ans;

void merge(node&now,node&l,node&r)
{
    now.len=l.len+r.len;
    now.p=new int[now.len];
    int p=0,p1=0,p2=0;

    while(p1<l.len&&p2<r.len)
    {
        if(l.p[p1]<r.p[p2])now.p[p++]=l.p[p1++];
        else now.p[p++]=r.p[p2++];
    }

    while(p1<l.len)
        now.p[p++]=l.p[p1++];
    
    while(p2<r.len)
        now.p[p++]=r.p[p2++];
 
}

void build(int x,int l,int r)
{
    if(l==r)
    {
        t[x].p=new int[1];
        t[x].len=1;
        t[x].p[0]=b[l].id;
        return;
    }
    
    int mid=l+r>>1;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    merge(t[x],t[x<<1],t[x<<1|1]);
}

//问左子树多少个数字的id在L，R之间，如果大于k，去左子树，如果小于k，去右子树，如果k等于0，那么得到答案
void query(int x,int l,int r,int L,int R,int k)
{
    if(l==r)
    {
        ans=b[l].val;
        return;
    }

    int left=x<<1;

    //第一个是lower，第二个是upper，
    int cntl=lower_bound(t[left].p,t[left].p+t[left].len,L)-t[left].p;
    int cntr=upper_bound(t[left].p,t[left].p+t[left].len,R)-t[left].p-1;
    int mid=l+r>>1;

    if(cntr-cntl+1>=k)query(x<<1,l,mid,L,R,k);
    else query(x<<1|1,mid+1,r,L,R,k-(cntr-cntl+1));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;++i)
    {
        cin>>b[i].val;
        b[i].id=i;
    }

    sort(b+1,b+1+n,cmp);

    build(1,1,n);

    while(m--)
    {
        cin>>l>>r>>k;

        query(1,1,n,l,r,k);
        cout<<ans<<'\n';
    }
    
    cout<<endl;
    system("pause");
    return 0;
}
