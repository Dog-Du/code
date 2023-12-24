#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include<queue>

#define ll long long

using namespace std;

const int maxn=5e3+10;

struct EDGE{
    int next,to,w;
}edge[maxn<<1];

int head[maxn],cnt=1,n,m,dist[maxn],used[maxn],tot[maxn];

void add(int x,int y,int w)
{
    edge[cnt]={head[x],y,w};
    head[x]=cnt++;
}

bool spfa(int s)
{
    for(int i=1;i<=n;++i)
    {
        dist[i]=1e9+10;
    }

    dist[s]=0;
    queue<int> que;
    que.push(s);
    used[s]=1;

    while(!que.empty())
    {
        int j=que.front();
        que.pop();
        used[j]=0;

        for(int i=head[j],v;i;i=edge[i].next)
        {
            v=edge[i].to;

            if(dist[v]>dist[j]+edge[i].w)
            {
                dist[v]=dist[j]+edge[i].w;

                if(++tot[v]>=n+1)return true;

                if(!used[v])
                {
                    que.push(v);
                    used[v]=1;
                }
            }
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    cin>>n>>m;

    for(int i=1,x,y,z;i<=m;++i)
    {
        cin>>x>>y>>z;
        add(y,x,z);
    }

    for(int i=1;i<=n;++i)
    {
        add(n+1,i,0);
    }

    if(spfa(n+1))cout<<"NO\n";
    else 
    {
        for(int i=1;i<=n;++i)
            cout<<dist[i]<<' ';
    }

    cout<<endl;
    system("pause");
    return 0;
}
