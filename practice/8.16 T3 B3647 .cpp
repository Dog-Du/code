#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

#define ll long long

using namespace std;

const int maxn=1e2+10;

int graph[maxn][maxn];

int n,m;

void add(int x,int y,int w)
{
    graph[x][y]=w;
    graph[y][x]=w;
}

void flody()
{

    for(int i=1;i<=n;++i)graph[i][i]=0;
    
    for(int k=1;k<=n;++k)
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                graph[i][j]=
                    min(graph[i][j],graph[i][k]+graph[k][j]);
}




int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    
    cin>>n>>m;

    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            graph[i][j]=1e9+10;
    
    for(int i=1,x,y,z;i<=m;++i)
    {
        cin>>x>>y>>z;
        add(x,y,z);
    }

    flody();

    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
            cout<<graph[i][j]<<' ';
        
        cout<<'\n';
    }

    cout<<endl;
    system("pause");
    return 0;
}
