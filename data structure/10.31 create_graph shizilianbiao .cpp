#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn=1e3+10;

//十字链表表示,方便找出，也方便找入
struct ArcBox{
    int from,to;//from,to节点
    ArcBox*head=nullptr,*tail=nullptr;//下一个同头，下一个同尾
    int w;
};

struct VexNode{
    int data;
    ArcBox*firhead=nullptr,*firtail=nullptr;//第一个头，第一个尾
};

class Graph{
private:
    int vnum,arcnum;
    VexNode vert[maxn];

public:
    Graph(){
        vnum=arcnum=0;
    }

    Graph(int x,int y)
    {
        vnum=x;
        arcnum=y;
    }

    void addedge(int x,int y,int w)
    {
        //先修改出
        ArcBox*temp=vert[x].firhead;
        vert[x].firhead=new ArcBox;
        vert[x].firhead->head=temp;

        //修改数据
        temp=vert[x].firhead;
        temp->from=x;
        temp->to=y;
        temp->w=w;
        
        //再修改入
        temp=vert[y].firtail;
        vert[y].firtail=vert[x].firhead;
        vert[y].firtail->tail=temp;
    }

    void show()
    {
        for(int i=0;i<=vnum;++i)
        {
            printf("%d : : \n\n",i);

            for(ArcBox* j=vert[i].firhead;j!=nullptr;j=j->head)
            {
                printf("head : %d %d\n",j->to,j->w);
            }

            for(ArcBox*j=vert[i].firtail;j!=nullptr;j=j->tail)
            {
                printf("tail : %d %d\n",j->from,j->w);
            }
        }
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    int n,m;
    cin>>n>>m;

    Graph it(n,m);

    while(m--)
    {
        int x,y,w;
        cin>>x>>y>>w;

        it.addedge(x,y,w);
    }

    it.show();

    cout<<endl;
    system("pause");
    return 0;
}
