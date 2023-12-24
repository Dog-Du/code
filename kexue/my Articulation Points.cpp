#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>

#define ll long long

using namespace std;

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

        set<size_t>& get_arc(size_t x){return graph[x];}
        
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
    char op;
    cout<<"please input how do you want to input :(H is hand and F is file)"<<endl;
    cin>>op;

    MyGraph::my_graph graph(0);

    int query=0;//query为询问或者操作次数

    //手写输入 graph数据
    if(op=='H')
        read_data_by_input(graph,query);
    else
    {
        // 通过文件输入graph数据，其他的还是手动输入 
        string filename;
        cin>>filename;
        read_data_by_file(filename,graph,query);
    }

    //获得结果。res里面全都是割点
    set<int> res;
    vector<int> around[graph.getvnum()+1];//保存父亲和孩子，用于modify函数
    Tarjan(graph,res,around);//先初始化

    cout<< "let's start to query :"<<endl;

    while(query--)
    {
        cout<<endl;
        cout<<"Q is querying one point whether is key point or not"<<endl;
        cout<<"S is outputting all key points"<<endl;
        cout<<"M is modifying a key point to a not key point"<<endl;
        cout<<endl;

        cin>>op;
        int x;

        if(op=='Q')//询问x点是不是割点
        {
            cin>>x;

            cout<< x << " is " << (res.count(x)?"":"not") << " key point" <<endl;
        }
        else if(op=='S')//输出所有割点
        {
            cout<<"the number of all key points is "<< res.size()<<" :"<<endl;
            for(auto&it:res)
                cout<<it<<' ';
            cout<<endl;
        }
        else if(op=='M')// 把某个点修改成非割点
        {
            cin>>x;

            //如果是，则修改
            if(res.count(x))
            {
                modify(x,graph,around);

                for(int i=0;i<=graph.getvnum();++i)
                    around[i].clear();
                
                res.clear();
                Tarjan(graph,res,around);
                cout<< "modify finished"<<endl;
            }
            else//如果不是，不修改
            {
                cout<< "this point is not key point" <<endl;
            }
        }
    }

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
