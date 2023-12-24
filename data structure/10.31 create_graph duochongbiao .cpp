#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

//多重邻接表
const int maxn=1e3+10;

struct EBox{
    int mark=0;
    int i,j;//边的两个点,
    EBox * ilink=nullptr,*jlink=nullptr;//一个指向i的下一个，一个指向j的下一个
    int w;
};

struct VexBox{
    int data;
    EBox * firarc=nullptr;//这里记录的是第一个出
};

class Graph{
private:
    int vnum=0,arcnum=0;
    VexBox vert[maxn];

public:

    EBox* getArc(int x){
        return vert[x].firarc;
    }
    int getvnum(){
        return vnum;
    }
    int getarcnum(){
        return arcnum;
    }
    Graph(int x){
        vnum=x,arcnum=0;
    }
    void addedge(int x,int y,int w){
        //新建边并修改
        EBox * p=new EBox;
        p->i=x;
        p->j=y;
        p->w=w;
        p->ilink=vert[p->i].firarc;
        p->jlink=vert[p->j].firarc;
        vert[p->i].firarc=p;//插入
        vert[p->j].firarc=p;//插入

        ++arcnum;
    }

    void show()
    {
        for(int i=0;i<=vnum;++i)
        {
            printf("%d : \n\n",i);

            for(EBox*j=vert[i].firarc;j!=nullptr;)
            {
                //要对那个是头，那个是尾，进行分类讨论，毕竟点是不一样的
                if(i==j->i)
                {
                    printf("%d %d\n",j->j,j->w);
                    j=j->ilink;
                }
                else
                {
                    printf("%d %d\n",j->i,j->w);
                    j=j->jlink;
                }
            }
        }
    }
};
