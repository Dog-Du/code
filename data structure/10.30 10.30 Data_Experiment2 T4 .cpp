#include <iostream>
#include <cstring>
#include <map>
#include <queue>
#define ll long long

using namespace std;

const int maxn=1e2+10;
pair<int,int> answer[maxn];
int cnt=0;

int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};

void dfs(pair<int,int> now,int graph[maxn][maxn],pair<int,int>&end,pair<int,int> answer[],int &cnt,const int & n)
{
    if(now==end)
    {
        for(int i=0;i<cnt;++i)
            cout<<answer[i].first<<' '<<answer[i].second<<endl;
        cout<<endl<<endl;

        return;
    }

    pair<int,int> t=now;

    for(int i=0;i<4;++i)
    {
        t.first=now.first+dx[i];
        t.second=now.second+dy[i];

        if(graph[t.first][t.second]==1||graph[t.first][t.second]==-1||
        t.first<=0||t.first>n||t.second<=0||t.second>n)continue;

        graph[t.first][t.second]=-1;
        answer[cnt++]=t;
        dfs(t,graph,end,answer,cnt,n);
        --cnt;
        graph[t.first][t.second]=0;
    }

    return;
}

void print(int x,map<int,int> & mp,pair<int,int>&a,int &n)
{
    if(x/n==a.first&&x%n==a.second)
    {
        cout<< a.first + 1<<' '<<a.second + 1<<endl;
        return;
    }

    print(mp[x],mp,a,n);

    cout<< x/n +1 <<' '<< x%n + 1 <<endl;
}

void bfs(pair<int,int> a,pair<int,int>&b,int graph[maxn][maxn],int &n)
{
    queue<pair<int,int>> que;
    --a.first,--a.second;
    --b.first,--b.second;

    que.push(a);
    map<int,int> mp;

    while(!que.empty())
    {
        pair<int,int> j=que.front(),t;
        que.pop();

        if(j==b)break;
        
        for(int i=0;i<4;++i)
        {
            t.first=j.first+dx[i];
            t.second=j.second+dy[i];

            if(graph[t.first][t.second]==1||graph[t.first][t.second]==-1||
                t.first<0||t.first>=n||t.second<0||t.second>=n)continue;
            
            graph[t.first][t.second]=-1;
            mp[t.first*n+t.second]=j.first*n+j.second;
            que.push(t);
        }
    }

    print(b.first*n+b.second,mp,a,n);
}

int main()
{
    int n,m;
    int graph[maxn][maxn];

    memset(graph,0,sizeof graph);
    pair<int,int> a,b,t;

    cin>>n>>a.first>>a.second>>b.first>>b.second;

    cin>>m;

    while(m--)
    {
        cin>>t.first>>t.second;
        graph[t.first][t.second]=1;
    }

    answer[cnt++]=a;
    //dfs(a,graph,b,answer,cnt,n);

    bfs(a,b,graph,n);

    cout<<endl;
    system("pause");
    return 0;
}

