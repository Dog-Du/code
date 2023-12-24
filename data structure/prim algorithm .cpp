#include "10.31 create_graph linjiebiao .cpp"

int n,m;
int a[maxn];

void prim(Graph&it)
{
    for(int i=1;i<=n;++i)
    {
        a[i]=INT32_MAX;
    }

    a[1]=0;

    int j=1,cnt=0,ans=0;

    while(cnt<=n-1)
    {
        for(int i=1;i<=n;++i)
            if(a[i]!=-1&&a[i]<a[j])
                j=i;
        
        ans+=a[j];
        a[j]=-1;
        ++cnt;

        for(ArcNode*k=it.getArc(j);k!=nullptr;k=k->next)
        {
            if(a[k->to]!=-1)
            {
                a[k->to]=min(a[k->to],k->w);
                j=k->to;//不然会出现，这次的标记为-1之后，j不再刷新
            }
        }

        for(int i=1;i<=n;++i)
            cout<<a[i]<<' ';
        
        cout<<endl;
    }

    cout<<ans<<endl;
}

int main()
{
    cin>>n>>m;

    Graph it(n);

    while(m--)
    {
        int x,y,z;
        cin>>x>>y>>z;
        it.addedge(x,y,z);
        it.addedge(y,x,z);
    }

    prim(it);

    cout<<endl;
    system("pause");
    return 0;
}
