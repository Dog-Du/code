#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include<deque>
#define ll long long

using namespace std;

//线段树写法，下面有单调队列写法
const int maxn=1e6+10;

int n,k;

struct node{
    int maxn,minn;
}t[maxn<<2],ans[maxn];

void pushup(node &x,node & l,node & r)
{
    x.maxn=max(l.maxn,r.maxn);
    x.minn=min(l.minn,r.minn);
}

void build(int x,int l,int r)
{
    if(l==r)
    {
        cin>>t[x].minn;
        t[x].maxn=t[x].minn;
        return;
    }

    int mid=l+r>>1;

    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);

    pushup(t[x],t[x<<1],t[x<<1|1]);
}

node query(int x,int l,int r,int L,int R)
{
    if(l>=L&&r<=R)return t[x];

    int mid=l+r>>1;
    node ans;
    ans.maxn=-1e9,ans.minn=1e9;
    node tl=ans,tr=ans;

    if(mid>=L)tl=query(x<<1,l,mid,L,R);
    if(mid<R)tr=query(x<<1|1,mid+1,r,L,R);

    pushup(ans,tl,tr);

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin>>n>>k;

    build(1,1,n);

    for(int i=k;i<=n;++i)
        ans[i]=query(1,1,n,i-k+1,i);
    
    for(int i=k;i<=n;++i)cout<<ans[i].minn<<' ';
    cout<<'\n';
    for(int i=k;i<=n;++i)cout<<ans[i].maxn<<' ';

    cout<<endl;
    system("pause");
    return 0;
}
//双向队列实现的单调队列
// const int maxn=1e6+10;

// int n,k;
// int a[maxn],ans1[maxn],ans2[maxn];

// struct QUEUE{
//     deque<int> q1,q2;

//     void push1(int x)//getmax
//     {
//         while(!q1.empty()&&q1.front()<=x-k)q1.pop_front();

//         while(!q1.empty()&&a[q1.back()]<a[x])q1.pop_back();

//         q1.push_back(x);
//     }

//     int getmax()
//     {
//         return a[q1.front()];
//     }

//     void push2(int x)
//     {
//         while(!q2.empty()&&q2.front()<=x-k)q2.pop_front();

//         while(!q2.empty()&&a[q2.back()]>a[x])q2.pop_back();

//         q2.push_back(x);
//     }

//     int getmin()
//     {
//         return a[q2.front()];
//     }
// }que;

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0),cout.tie(0);

    
//     cin>>n>>k;

//     for(int i=1;i<=n;++i)cin>>a[i];

//     for(int i=1;i<=n;++i)
//     {
//         que.push1(i);
//         que.push2(i);

//         if(i>=k)
//         {
//             ans1[i]=que.getmin();
//             ans2[i]=que.getmax();
//         }
//     }

//     for(int i=k;i<=n;++i)cout<<ans1[i]<<' ';

//     cout<<'\n';

//     for(int i=k;i<=n;++i)cout<<ans2[i]<<' ';


//     cout<<endl;
//     system("pause");
//     return 0;
// }
