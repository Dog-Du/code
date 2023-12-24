#include "10.31 create_graph linjiebiao .cpp"
#include <bitset>

//求传递闭包，时间复杂度没有明显提升，从 O(n*m) 变成了 O(n*max(n^2,m))

void floyd(int n,bitset<maxn> graph[])
{
    for(int k=1;k<=n;++k)
    {
        graph[k][k]=1;
        for(int i=1;i<=n;++i)
        {
            if(graph[i][k])
                graph[i]|=graph[k];
        }
    }
}

void solve()
{
    int n,m;
    cin>>n>>m;
    
    Graph it(n);
    bitset<maxn> graph[n+1];

    while(m--)
    {
        int x,y;
        cin>>x>>y;

        it.addedge(x,y,0);
    }

    //邻接表转化成邻接矩阵
    for(int i=1;i<=n;++i)
    {
        for(ArcNode*j=it.getArc(i);j!=nullptr;j=j->next)
        {
            graph[i][j->to]=1;
        }
    }
    
    //floyd算法求传递闭包
    floyd(n,graph);

    cout<<"answer:\n";
    
    for(int i=1;i<=n;++i)
    {
        if(graph[i].count()==n)
            cout<<i<<' ';
    }

    cout<<endl;
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
