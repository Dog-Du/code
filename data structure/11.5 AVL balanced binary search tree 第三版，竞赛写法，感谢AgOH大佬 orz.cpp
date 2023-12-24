#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn=1e6+10;


//LL表示左子树太高，且左子树的左子树比较高，以此类推LR，RL，RR
//太高指 bf >1 比较高指 bf>0

struct node{
    int l,r,p;
    int key,val;
    int height,size;//height表示高度,size表示这棵树的大小,bf可以现算
}avl[maxn];

int cnt,root;

void newnode(int &now,int val)
{
    avl[now=++cnt].val=val;
    avl[cnt].size=1;
    avl[cnt].key=1;
}

void update(int &now)//更新size和height
{
    avl[now].size=avl[avl[now].l].size+avl[avl[now].r].size+1;
    avl[now].height=max(avl[avl[now].l].height,avl[avl[now].r].height)+1;
}

int factor(int& now)
{
    return avl[avl[now].l].height-avl[avl[now].r].height;
}

void lrotate(int &now)
{
    int r=avl[now].r;
    avl[now].r=avl[r].l;
    avl[r].l=now;
    now=r;//更新值，

    update(avl[now].l),update(now);
}

void rrotate(int &now)
{
    int l=avl[now].l;
    avl[now].l=avl[l].r;
    avl[l].r=now;
    now=l;

    update(avl[now].r),update(now);
}

void check(int &now)//检查这个节点是否需要旋转，如果需要就旋转
{
    int bf=factor(now);

    if(bf>1)
    {
        int lf=factor(avl[now].l);
        if(lf>0)rrotate(now);//LL
        else lrotate(avl[now].l),rrotate(now);//LR
    }
    else if(bf<-1)
    {
        int rf=factor(avl[now].r);
        if(rf<0)lrotate(now);//RR
        else rrotate(avl[now].r),lrotate(now);//RL
    }
    else if(now)update(now);//非空，则更新一下
}

void ins(int &now,int val)
{
    if(!now)newnode(now,val);
    else if(val<avl[now].val)ins(avl[now].l,val);
    else if(val>avl[now].val)ins(avl[now].r,val);
    else
    {
        ++avl[now].key;
    }

    check(now);//回溯检查，自底向上的检查
}

int find(int &now,int fa)
{
    int ret;

    if(!avl[now].l)//找到了这个后继
    {
        ret=now;//他就是返回值
        avl[fa].l=avl[now].r;//把它的左儿子修改成该点的右儿子
    }
    else
    {
        ret=find(avl[now].l,now);//返回值继续找
        check(now);//然后检查，自顶向上检查
    }

    return ret;//返回编号
}

void del(int &now,int val)
{
    if(val==avl[now].val)
    {
        int l=avl[now].l,r=avl[now].r;

        if(!l||!r)now=l+r;//如果没有儿子或者只是单儿子，now变成左儿子或右儿子或0
        else
        {
            now=find(r,r);
            if(now!=r)
                avl[now].r=r;
            avl[now].l=l;
        }
    }
    else if(val<avl[now].val)del(avl[now].l,val);
    else if(val>avl[now].val)del(avl[now].r,val);

    check(now);//自顶向上检查
}

int search(int &x,int &val)
{
    if(x==0)return 0;
    else if(avl[x].val<val)return search(avl[x].r,val);
    else if(avl[x].val>val)return search(avl[x].l,val);
    else return x;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    int n;
    cin>>n;

    int a[n+1];

    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
        ins(root,a[i]);
    }

    sort(a+1,a+1+n);
    int tot=unique(a+1,a+1+n)-a-1;

    for(int i=1;i<=tot;++i)
    {
        int t=search(root,a[i]);
        t=avl[t].key;
        while(t--)cout<<a[i]<<' ';

        del(root,a[i]);
    }
    cout<<endl;
    system("pause");
    return 0;
}
