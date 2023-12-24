#include "10.31 create_graph duochongbiao .cpp"

//多重邻接表存图比较方便

int ind[maxn],top[maxn];//用完之后可以delete 这两个数组
bool judge[maxn];
int t;

void topsort(Graph &it)//topsort 预处理
{
    int n=it.getvnum();
    t=0;

    for(int i=1;i<=n;++i)
    {
        for(EBox*j=it.getArc(i);j!=nullptr;)
        {
            if(j->mark==1){
                if(j->i==i)j=j->ilink;
                else j=j->jlink;
                continue;
            }

            j->mark=1;

            if(j->i==i){
                ++ind[j->j];
                ++ind[i];
                j=j->ilink;
            }
            else{
                ++ind[j->i];
                ++ind[i];
                j=j->jlink;
            }

        }
    }

    for(int i=1;i<=n;++i)
        if(ind[i]<=1)top[t++]=i;
    
    int p=0;

    while(p<t)//topsort
    {
        for(EBox*j=it.getArc(top[p]);j!=nullptr;)
        {
            if(j->mark==2)
            {
                if(j->i==top[p])j=j->ilink;
                else j=j->jlink;
                continue;
            }

            j->mark=2;

            if(j->i==top[p]){
                if(--ind[j->j]==1)top[t++]=j->j;
                j=j->ilink;
            }
            else{
                if(--ind[j->i]==1)top[t++]=j->i;
                j=j->jlink;
            }

        }

        judge[top[p++]]=1;
    }

}

bool check(int x)
{
    return judge[x]==0;
}

void solve()
{
    int n, m, t;
    cin >> n >> m >> t;
    Graph it(n);

    while (m--)
    {
        int x, y;
        cin >> x >> y;
        it.addedge(x, y, 0);
    }

    topsort(it);//预处理

    while(t--)
    {
        int x;
        cin>>x;

        cout<<check(x)<<endl;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    cout << endl;
    system("pause");
    return 0;
}
