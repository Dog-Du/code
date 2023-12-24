#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include<queue>

using namespace std;

const int maxn=1e4+10;

struct EDGE{
    int next,to,weigh;
}edge[maxn<<1];

int n,m,cnt=1,head[maxn],used[maxn],dis[maxn],point[maxn];

void add(int x,int y,int w)
{
    edge[cnt]={head[x],y,w};
    head[x]=cnt++;
}

bool spfa()
{
    for(int i=1;i<=n;++i)
    {
        dis[i]=1e9+10;
        used[i]=0;
        point[i]=0;
    }

    queue<int> que;
    que.push(1);
    used[1]=1;
    dis[1]=0;

    while(!que.empty())
    {
        int j=que.front();
        que.pop();
        used[j]=0;

        for(int i=head[j],v;i;i=edge[i].next)
        {
            v=edge[i].to;
            if(dis[v]>edge[i].weigh+dis[j])
            {
                dis[v]=edge[i].weigh+dis[j];

                if(!used[v])
                {
                    que.push(v);
                    used[v]=1;

                    if(++point[v]>=n)return true;
                }
            }
        }
    }

    return false;
}

void solve()
{
    cin>>n>>m;

    cnt=1;
    for(int i=1;i<=2*m;++i)head[i]=0;

    for(int i=1,x,y,z;i<=m;++i)
    {
        cin>>x>>y>>z;

        if(z>=0)
        {
            add(x,y,z);
            add(y,x,z);
        }
        else    
            add(x,y,z);
    }

    if(spfa())cout<<"YES\n";
    else cout<<"NO\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    
    int t;

    cin>>t;

    while(t--)
    {
        solve();
    }

    cout<<endl;
    system("pause");
    return 0;
}
