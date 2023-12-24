#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

#define ll long long

using namespace std;

const int INF=1e9+10;
const int maxn=1e3+10;

struct pathnode{
    int pre,len;
};

int graph[maxn][maxn];
pathnode path[maxn];

void dj(int x,int n)
{
    bool used[n+1];
    int dist[n+1];
    for(int i=1;i<=n;++i)
    {
        used[i]=0;
        dist[i]=INF;
    }

    dist[x]=0;
    path[x].len=0;
    path[x].pre=x;

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> que;

    que.push({0,x});

    while(!que.empty()){
        int now=que.top().second;
        que.pop();
        if(used[now])continue;
        used[now]=1;
        
        for(int k=1;k<=n;++k)
            if(graph[now][k]!=INF&&dist[k]>dist[now]+graph[now][k]){
                dist[k]=dist[now]+graph[now][k];
                path[k].len=path[now].len+1;
                path[k].pre=now;
                if(!used[k])que.push({dist[k],k});
            }
        
    }
}

void solve(){
    int n,m,x;
    cin>>n>>m>>x;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            graph[i][j]=INF;
    for(int i=1;i<=m;++i){
        int x,y,z;
        cin>>x>>y>>z;
        graph[x][y]=graph[y][x]=z;
    }
    dj(x,n);
    int j=x;
    for(int i=1;i<=n;++i){
        if(path[i].len>path[j].len)
            j=i;
    }
    cout<<"len:"<<path[j].len<<endl;
    while(j!=x)
    {
        cout<<j<<"<-";
        j=path[j].pre;
    }
    cout<<x<<endl<<endl;
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
