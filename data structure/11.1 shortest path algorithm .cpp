#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn = 1e5 + 10;

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
    int vnum, arcnum;
    VNode vert[maxn];

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

    Graph(int x, int y)
    {
        vnum = x;
        arcnum = y;
    }

    void addedge(int x, int y, int w)
    {
        ArcNode *temp = vert[x].firarc;
        vert[x].firarc = new ArcNode;
        vert[x].firarc->next = temp;

        temp = vert[x].firarc;
        temp->to = y;
        temp->w = w;
    }

    void show()
    {
        for (int i = 0; i <= vnum; ++i)
        {
            printf("%d : \n", i);

            for (ArcNode *j = vert[i].firarc; j != nullptr; j = j->next)
            {
                printf("%d %d\n", j->to, j->w);
            }

            printf("\n");
        }
    }
};

#include <queue>

int n,m;
void dj(Graph&it)
{
    struct node{
        int x,w;
        bool operator<(const node&it)const{
            return w>it.w;
        }
    };

    int path[n+1];
    //表示节点i的最短路径上的直接前驱，最后递归式的最后向前就可以得到路径,自底向上的方法得到路径
    int dist[n+1],used[n+1];
    priority_queue<node> que;

    for(int i=1;i<=n;++i)
    {
        dist[i]=1e9+1;
        used[i]=0;
        path[i]=-1;
    }

    dist[1]=0;

    que.push({1,0});

    while(!que.empty())
    {
        int j=que.top().x;
        que.pop();

        if(used[j])continue;
        used[j]=1;

        for(ArcNode*k=it.getArc(j);k!=nullptr;k=k->next)
        {
            if(dist[k->to]>dist[j]+k->w)
            {
                dist[k->to]=dist[j]+k->w;
                path[k->to]=j;//更新k->to的前驱
                if(!used[k->to])
                    que.push({k->to,dist[k->to]});
            }
        }
    }

    for(int i=2;i<=n;++i)
    {
        int t=i;

        while(t!=1)
        {
            cout<<t<<"<-";
            t=path[t];
        }

        cout<<t<<endl;
    }

    for(int i=1;i<=n;++i)
        cout<<dist[i]<<' ';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    int k;
    cin>>n>>m>>k;
    Graph it(n,m);
    
    while(m--)
    {
        int x,y,z;
        cin>>x>>y>>z;
        it.addedge(x,y,z);
    }

    dj(it);

    cout<<endl;
    system("pause");
    return 0;
}
