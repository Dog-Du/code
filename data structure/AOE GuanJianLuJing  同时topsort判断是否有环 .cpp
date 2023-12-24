#include "10.31 create_graph linjiebiao .cpp"
#include <map>

//AOE 求关键路径，关键活动 关键路径上的全是关键活动
int n,m,t;//t为top数组长度
int a[maxn],ind[maxn];//a为top数组
int ve[maxn],vl[maxn];//ve是节点最早发生，vl是节点最晚发生
map<pair<int,int>,int> e,l;//e是活动最早发生，l是活动最晚发生

bool topsort(Graph&it)//top同时判断是否有环
{
    //有环等价于在top排序时，top数组长度小于节点个数，即可排序节点个数少于总个数
    int p=0;

    for(int i=1;i<=n;++i)
        if(ind[i]==0)a[t++]=i;
    
    while(p<t)
    {
        for(ArcNode* j=it.getArc(a[p]);j!=nullptr;j=j->next)
        {
            if(--ind[j->to]==0)
                a[t++]=j->to;
            else if(ind[j->to]<0)return true;//如果一个点的入度已经为零，但却被再一次相指，肯定有环
        }
        ++p;
    }

    cout<<"topsort: ";

    for(int i=0;i<t;++i)
        cout<<a[i]<<' ';
    cout<<endl<<endl;

    return t<n;
}

void AOE(Graph&it1,Graph&it2)//it1是正序，it2是逆序
{
    if(topsort(it1))return;

    ve[1]=0;//这里不太严谨，应该是入度为零的节点全为0

    for(int i=0;i<t;++i)
    {
        for(ArcNode*j=it1.getArc(a[i]);j!=nullptr;j=j->next)
        {
            ve[j->to]=max(ve[j->to],ve[a[i]]+j->w);//最早发生为前提节点最大值
        }
    }

    for(int i=1;i<=n;++i)//打印一下
        printf("%d:%d ",i,ve[i]);
    cout<<endl<<endl;

    for(int i=1;i<=n;++i)//把最晚发生至一个极大值
        vl[i]=1e9+10;

    vl[n]=ve[n];//赋初始值，这里一样也不太严谨，应该是出度为零的节点

    for(int i=t-1;i>=0;--i)
    {
        for(ArcNode*j=it2.getArc(a[i]);j!=nullptr;j=j->next)
        {
            vl[j->to]=min(vl[j->to],vl[a[i]]-j->w);//最晚发生是后面的最小值
        }
    }

    for(int i=1;i<=n;++i)
        printf("%d:%d ",i,vl[i]);
    cout<<endl<<endl;

    for(int i=0;i<t;++i)//求各个活动的最早发生时间
    {
        for(ArcNode*j=it1.getArc(a[i]);j!=nullptr;j=j->next)
        {
            e[{a[i],j->to}]=ve[a[i]];// (i,j)最早发生等于ve[i]
        }
    }

    cout<<"early time : ";
    for(auto&it:e)
    {
        cout<<it.first.first<<"->"<<it.first.second<<':'<<it.second<<' ';
    }
    cout<<endl<<endl;

    for(int i=t-1;i>=0;--i)//各个活动的最晚发生时间
    {
        for(ArcNode*j=it2.getArc(a[i]);j!=nullptr;j=j->next)
        {
            l[{j->to,a[i]}]=vl[a[i]]-j->w;// (i,j)最晚发生等于vl[j]-w(i,j)
        }
    }

    cout<<"last time : ";
    for(auto&it:l)
    {
        cout<<it.first.first<<"->"<<it.first.second<<':'<<it.second<<' ';
    }
    cout<<endl<<endl;

    cout<<"key activity : ";

    for(auto&it:e)
    {
        if(it.second==l[it.first])
        {
            cout<<it.first.first<<"->"<<it.first.second<<' ';
        }
    }

    cout<<endl<<endl;

    e.clear(),l.clear();
}

vector<int> path;
vector<vector<int>> res;//关键路径结果

void dfs(int x,Graph&it)//寻找关键路径
{
    path.push_back(x);

    if(it.getArc(x)==nullptr)
    {
        res.push_back(path);
    }

    for(ArcNode*j=it.getArc(x);j!=nullptr;j=j->next)
    {
        if(ve[j->to]==vl[j->to])//如果相等就继续
        {
            dfs(j->to,it);
        }
    }

    path.pop_back();
}

void solve()
{
    cin>>n>>m;

    Graph it1(n),it2(n);

    while(m--)
    {
        int x,y,z;
        cin>>x>>y>>z;
        ind[y]++;
        it1.addedge(x,y,z);
        it2.addedge(y,x,z);
    }

    AOE(it1,it2);
    dfs(1,it1);

    cout<<"key  paths : ";
    for(auto&iter:res)
    {
        for(auto&it:iter)
            cout<<it<<' ';
        cout<<endl;
    }
    cout<<endl;
}

int main()
{
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
