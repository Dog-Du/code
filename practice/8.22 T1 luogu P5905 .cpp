#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn=3e3+10;

struct EDGE{
    int next,to;
    ll w;
}edge[maxn<<2];

struct node{
    int x;
    ll w;
    bool operator<(const node&it)const
    {
        return w>it.w;
    }
};

int n,m,head[maxn<<1],tot[maxn<<1],cnt=1,used[maxn<<1];
ll high[maxn<<1],dist[maxn<<1];

void add(int x,int y,ll w)
{
    edge[cnt]={head[x],y,w};
    head[x]=cnt++;
}

bool spfa(int s)
{
    for(int i=1;i<=n;++i)
        high[i]=1e9;
    
    queue<int> que;
    que.push(s);
    used[s]=1;
    high[s]=0;

    while(que.size())
    {
        int j=que.front();
        que.pop();
        used[j]=0;

        for(int i=head[j],v;i;i=edge[i].next)
        {
            v=edge[i].to;

            if(high[v]>high[j]+edge[i].w)
            {
                high[v]=high[j]+edge[i].w;

                if(!used[v])
                {
                    que.push(v);
                    used[v]=1;

                    if(++tot[v]>=n+1)return true;
                }
            }
        }
    }
    return false;
}

void dj(int s)
{
    for(int i=1;i<=n;++i)
        dist[i]=1e9,used[i]=0;
    
    priority_queue<node> que;
    que.push({s,0});
    dist[s]=0;

    while(que.size())
    {
        int j=que.top().x;
        que.pop();
        if(used[j])continue;
        used[j]=1;

        for(int i=head[j],v;i;i=edge[i].next)
        {
            v=edge[i].to;

            if(dist[v]>dist[j]+edge[i].w)
            {
                dist[v]=dist[j]+edge[i].w;

                if(!used[v])que.push({v,dist[v]});
            }
        }

    }
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
    }

    for(int i=1;i<=n;++i)add(0,i,0);

    if(spfa(0))
    {
        cout<<-1;
        return 0;
    }

    for(int i=1;i<=n;++i)
        for(int j=head[i];j;j=edge[j].next)
            edge[j].w+=high[i]-high[edge[j].to];

    for(int i=1;i<=n;++i)
    {
        dj(i);

        ll ans=0;

        for(int j=1;j<=n;++j)
        {
            if(dist[j]==1e9)
                ans+=j*dist[j];
            else    
                ans+=j*(dist[j]+high[j]-high[i]);
        }

        cout<<ans<<'\n';
    }

    cout<<endl;
    system("pause");
    return 0;
}
