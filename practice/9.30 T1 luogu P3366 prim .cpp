#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include<fstream>
#include <vector>
#include <algorithm>
#include <queue>

//堆优化prim
#define ll long long

using namespace std;

const int maxn=2e5+10,N=123456789;

struct EDGE{
    int to,w,next;
}edge[maxn<<1];

struct node{
    int id,w;
    bool operator<(const node&it)const{
        return w>it.w;
    }
};

int n,m;
int cnt=1,head[maxn],dis[maxn];
bool used[maxn];

void add(int x,int y,int w)
{
    edge[cnt]={y,w,head[x]};
    head[x]=cnt++;
}

void prime(int s)
{
    for(int i=0;i<=n;++i)
        dis[i]=N;

    priority_queue<node> que;
    que.push({s,0});
    int tot=0,ans=0;

    while(!que.empty())
    {
        int j=que.top().id,w=que.top().w;
        que.pop(); 
        if(used[j])continue;
        used[j]=1;
        ans+=w;
        ++tot;

        for(int i=head[j],to;i;i=edge[i].next)
        {
            to=edge[i].to;
            
            if(!used[to]&&dis[to]>edge[i].w)
            {
                dis[to]=edge[i].w;
                que.push({to,dis[to]});
            }   
        }
    }

    if(tot<n)
    {
        cout<<"orz";
        return;
    }
    cout<<ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin>>n>>m;

    for(int i=1,x,y,w;i<=m;++i)
    {
        cin>>x>>y>>w;
        add(x,y,w);
        add(y,x,w);
    }

    prime(1);


    cout<<endl;
    system("pause");
    return 0;
}
