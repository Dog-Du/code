#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn = 1e3 + 10;

//邻接表
struct ArcNode
{ // 边
    int w, to;
    ArcNode *next;

    ArcNode()
    {
        w = 0, to = 0;
        next = nullptr;
    }
};

struct VNode
{ // 点
    int data;
    ArcNode *firarc;

    VNode()
    {
        data = 0;
        firarc = nullptr;
    }
};

class Graph
{
private:
    int vnum,arcnum;
    VNode vert[maxn];

    void dfs(int x,bool used[])
    {
        printf("%d ",x);
        for(ArcNode*j=getArc(x);j!=nullptr;j=j->next)
        {
            if(used[j->to])continue;
            used[j->to]=1;
            dfs(j->to,used);
            used[j->to]=0;
        }
    }
public:
    int getvnum()
    {
        return vnum;
    }

    int getarcnum()
    {
        return arcnum;
    }

    ArcNode * getArc(int x)
    {
        return vert[x].firarc;
    }

    Graph()
    {
        vnum = 0, arcnum = 0;
    }
    
    Graph(int x)
    {
        vnum=x;
        arcnum=0;
    }

    void addedge(int x, int y, int w)
    {
        ArcNode * p=new ArcNode;
        p->next=vert[x].firarc;
        p->w=w;
        p->to=y;

        vert[x].firarc=p;
        ++arcnum;
    }

    void dfs_search(int x)
    {
        bool used[vnum+1]={0};
        

        dfs(x,used);

        //delete [] used;
    }
};

// int main()
// {
//     int n,m;
//     cin>>n>>m;

//     Graph it(n,m);

//     while(m--)
//     {
//         int x,y,z;
//         cin>>x>>y>>z;

//         it.addedge(x,y,z);
//     }


//     it.dfs_search(1);

//     cout<<endl;
//     system("pause");
//     return 0;
// }