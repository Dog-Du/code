#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

//01前缀树实现map功能，从低位到高位进行操作

const int maxlog = 32;

class Tire01
{
private:
    struct node//child[0]是0，child[1]是1。前缀
    {
        node *child[2];
        int size,value;
        node(node *p)
        {
            child[0] = child[1] = p;
            size = 0;
        }
    } *root;

    void clear(node*now)
    {
        if(now==root)return;
        clear(now->child[0]);
        clear(now->child[1]);
        delete now;
    }

public:

    void clear()
    {
        clear(root->child[0]);
        clear(root->child[1]);
        root->child[0]=root->child[1]=root;
    }

    ~Tire01()
    {
        clear();
        delete root;
    }

    Tire01()//设置头结点root，让所有空节点都指向root
    {
        root = new node(nullptr);
        root->child[0] = root->child[1] = root;
    }

    void insert(int x,int value)
    {
        node *p = root;
        int t;

        while(x)//从最低位开始，到最高位结束
        {
            t = x & 1;//这一位上的数字是0还是1
            x>>=1;

            if (p->child[t] == root)
                p->child[t] = new node(root);//如空，则新建

            p = p->child[t];
            ++p->size;
        }

        p->value=value;

        //如果之前这个地方已经插入过了，那么应该清除这次的size记录
        if(p->size==p->child[0]->size+p->child[1]->size)
        {
            for (int i = 0; i <= maxlog && x; ++i)
            {
                p = p->child[x>>i&1];
                --p->size;
            }
        }

    }

    void erase(int x)//删除则更简单，直接沿路删除即可，因为不需要释放空间，
    {
        node *p = root;

        for (int i = 0; (x>>i) ; ++i)
        {
            p = p->child[x>>i&1];
            --p->size;

            if(p==root)break;
        }

        //如果不存在这个值，那么删除应该失败，所以把size加回来。
        if(p->size==p->child[0]->size+p->child[1]->size||p==root)
        {
            for (int i = 0; i <= maxlog && x; ++i)
            {
                p = p->child[x>>i&1];
                ++p->size;
            }
        }
    }

    node* search(int x)
    {
        node *p = root;

        while(x)
        {
            p = p->child[x&1];
            x>>=1;

            if(p==root)break;
        }

        //如果查询的非存value的节点，那么返回nullptr。
        if(p->size==p->child[0]->size+p->child[1]->size||p==root)return nullptr;
        return p;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    Tire01 it;
    int n;
    cin >> n;

    int a[n+1];
    
    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
        
        auto res=it.search(a[i]);

        //实际上stl中[]符号返回的是引用，如果不存在则新建，我这里没有新建，所以毕竟先查询一次探探路
        if(res==nullptr)it.insert(a[i],1);//如果空，插入1
        else it.insert(a[i],res->value+1);//不为空，则+1
    }

    sort(a+1,a+1+n);

    int tot=unique(a+1,a+1+n)-a-1;

    for(int i=1;i<=tot;++i)
    {
        auto res=it.search(a[i]);

        while(res->value--)
        {
            cout<<a[i]<<' ';
        }
        
        it.erase(a[i]);
    }

    cout << endl;
    system("pause");
    return 0;
}