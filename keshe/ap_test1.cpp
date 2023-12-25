#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>

#define ll long long

using namespace std;

//可以通过洛谷P3369割点
//https://www.luogu.com.cn/problem/P3388

namespace MyGraph
{
    class my_graph
    {
    private:
        typedef unsigned long long size_t;

        vector<set<size_t>> graph;//为了防止输入重复边，使用set
        size_t arcnum;
    public:
        my_graph(size_t x):arcnum(0){graph.resize(x+1);}
        ~my_graph(){graph.clear();arcnum=0;}

        const set<size_t>& get_arc(size_t x){return graph[x];}
        
        void resize(size_t x){graph.resize(x+1);}
        size_t getvnum(){return graph.size()-1;}
        size_t getarcnum(){return arcnum;}
        void add_edge(size_t x,size_t y){if(x==y||graph[x].count(y))return;graph[x].insert(y);++arcnum;}
    };
}

void dfs(int now,MyGraph::my_graph&graph,int low[],int is_key[],set<int>&key_point,int dfn[],int &root,int &cnt,vector<int> around[])
{
    dfn[now]=low[now]=++cnt;
    int son=0;

    for(auto&it:graph.get_arc(now))
    {
        if(dfn[it]==0)
        {
            ++son;
            dfs(it,graph,low,is_key,key_point,dfn,root,cnt,around);

            around[now].push_back(it);
            around[it].push_back(now);

            low[now]=min(low[now],low[it]);

            if(low[it]>=dfn[now]&&now!=root&&is_key[now]==0)
                key_point.insert(now),is_key[now]=1;
        }
        else
            low[now]=min(low[now],dfn[it]);
    }

    if(root==now&&son>=2&&is_key[now]==0)
        key_point.insert(now),is_key[now]=1;
}

void Tarjan(MyGraph::my_graph& graph,set<int>&key_point,vector<int> around[])
{
    int dfn[graph.getvnum()+1]={0},low[graph.getvnum()+1]={0},is_key[graph.getvnum()+1]={0};

    int root=0,cnt=0;

    for(int i=0;i<=graph.getvnum();++i)
    {
        if(dfn[i]==0)
        {
            root=i;
            dfs(i,graph,low,is_key,key_point,dfn,root,cnt,around);
        }
    }

}

//通过文件输入
void read_data_by_file(string &filename,MyGraph::my_graph &graph,int&query)
{
    // 打开文件
    ifstream infile(filename);
    if (!infile.is_open())
    {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    int n, m; // 图的顶点数和边数
    infile >> n >> m;

    // 初始化图
    graph.resize(n);

    // 读入图的边信息
    for (int i = 0; i < m; ++i)
    {
        int x, y;
        infile >> x >> y;
        graph.add_edge(x, y);
        graph.add_edge(y, x); // 无向图需添加反向边
    }

    // 将新图赋值给传入的图对象

    // 读入查询次数
    infile >> query;
    
    // 关闭文件
    infile.close();
}


//通过手动输入
void read_data_by_input(MyGraph::my_graph&graph,int&query)
{
    int n, m; // 顶点数和边数
    cout << "please input point number and edge number :" << endl;
    cin >> n >> m;

    // 初始化图
    MyGraph::my_graph new_graph(n);

    // 读入图的边信息
    cout << "please input the two ends of every edge :" << endl;
    for (int i = 0; i < m; ++i)
    {
        int x, y;
        cin >> x >> y;
        new_graph.add_edge(x, y);
        new_graph.add_edge(y, x); // 无向图需添加反向边
    }

    // 将新图赋值给传入的图对象
    graph = new_graph;

    // 读入查询次数
    cout << "please input how many do you want to query :" << endl;
    cin >> query;
}

//把 x点修改为非割点
void modify(int x,MyGraph::my_graph& graph,vector<int> around[])
{
    for(int i=1;i<around[x].size();++i)
    {
        graph.add_edge(around[x][i],around[x][i-1]);
        graph.add_edge(around[x][i-1],around[x][i]);
    }
}

void solve()
{
    int n,m;
    cin>>n>>m;
    MyGraph::my_graph graph(n);

    for(int i=1,x,y;i<=m;++i)
    {
        cin>>x>>y;
        graph.add_edge(x,y);
        graph.add_edge(y,x);
    }

    set<int> res;
    vector<int> around[n+1];

    Tarjan(graph,res,around);

    cout<<res.size()<<'\n';

    for(auto &it:res)
        cout<<it<<' ';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    int t=1;
    //cin>>t;

    while(t--)
    {
        solve();
    }    


    cout<<endl;
    system("pause");
    return 0;
}