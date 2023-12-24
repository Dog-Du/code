#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn=1e3+10;

bool graph[maxn][maxn];
vector<pair<int,int>> path,bestpath;
int n,m,xs,ys,xe,ye;

int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};

void dfs(int x,int y)
{
    if(x==xe&&y==ye)
    {
        if(bestpath.size()==0)bestpath=path;
        if(bestpath.size()>path.size())bestpath=path;

        for(auto&it:path)
            cout<<it.first<< ' '<<it.second<<endl;
        cout<<endl;
        return;
    }

    for(int i=0,nx,ny;i<4;++i)
    {
        nx=x+dx[i];
        ny=y+dy[i];

        if(nx<1||nx>n||ny<1||ny>m||graph[nx][ny]==1)continue;

        graph[nx][ny]=1;
        path.push_back({nx,ny});

        dfs(nx,ny);

        graph[nx][ny]=0;
        path.pop_back();
    }
}

int main()
{
    int k;
    cin>>n>>m>>k>>xs>>ys>>xe>>ye;

    while(k--)
    {
        int x,y;
        cin>>x>>y;

        graph[x][y]=1;
    }

    path.push_back({xs,ys});
    graph[xs][ys]=1;
    dfs(xs,ys);

    for(auto&it:bestpath)
        cout<<it.first<<' '<<it.second<<endl;
        
    cout<<endl;
    system("pause");
    return 0;
}
