#include "10.31 create_graph linjiebiao .cpp"

void dfs(int x,Graph&it,bool used[])
{
    used[x]=1;

    for(ArcNode*j=it.getArc(x);j!=nullptr;j=j->next)
    {
        if(used[j->to])continue;
        dfs(j->to,it,used);
    }
}

bool check(int x,Graph&it)
{
    int n=it.getvnum();
    bool used[n+1]={0};

    dfs(x,it,used);

    for(int i=1;i<=n;++i)
        if(!used[i])return false;
    
    return true;
}   

void solve()
{
    int n,m;
    cin>>n>>m;

    Graph it(n);

    while(m--)
    {
        int x,y;
        cin>>x>>y;
        it.addedge(x,y,0);
    }

    cout<<"answer:"<<endl;

    for(int i=1;i<=n;++i)
    {
        if(check(i,it))
            cout<<i<<endl;
    }

    cout<<endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    int n;
    cin>>n;

    while(n--)
    {
        solve();
    }

    cout<<endl;
    system("pause");
    return 0;
}
