#include <iostream>
#include <random>
#include <ctime>

#define ll long long

using namespace std;

//总结： skip list简单好写，空间复杂度为 O(p*MAX_LEVEL*n)，p为创建新节点的时候的概率，再这段程序中是1/4，
//因为skip list完全支持线性读写，所以将它封装成一个泛型容器也不困难，尤其是迭代器也很好写，但是因为要支持--操作的可能需要改写成双向链表。

const int N=1e5+10,MAX_LEVEL=12;//最大层数

std::random_device seed;
std::minstd_rand rng(seed());//生成随机数

struct Node{
    int level;//其实写一个const，但是懒得弄了。
    ll key;
    
    struct nodePointer{
        int span;//跨幅，方便get_rank,get_val，类似于平衡树中的node_count
        Node*pointer;
        nodePointer():span(0),pointer(nullptr){}//让它新建的时候为空。
        nodePointer(Node*x):span(0),pointer(x){}
        Node*operator->(){return pointer;}
        operator Node*(){return pointer;}
    }*next;//一个节点在生成的时候已经决定了它的level，这个是不会在改变的

    ~Node(){delete [] next;}//析构时删除next数组

    Node():key(0),level(0){}
};

Node* new_node()
{
    return new Node;
}

void del_node(Node* x)
{
    delete x;
}

int random_level()//产生随机高度，其中， (rng()&1)&&(rng()&1) 表示 概率为 1/4
{
    int ret=1;
    while(ret<MAX_LEVEL&&(rng()&1)&&(rng()&1))
        ++ret;
    return ret;
}

Node* create_node(const int &level,const ll & key)//生成一个节点
{
    Node*ret=new_node();
    ret->key=key;
    ret->level=level;
    ret->next=new Node::nodePointer[level];
    return ret;
}

Node*head=create_node(MAX_LEVEL,0);//head为头结点，减少分类讨论，显然他一定是最高的层数
int level=0,length=0;

void insert(const ll &key)
{
    Node*cur=head;
    Node::nodePointer update[MAX_LEVEL];
    int lst_pos[MAX_LEVEL+1];//记录每一层上一个节点的位置！！也就是下标。这是在为维护span做服务
    lst_pos[level]=0;//因为下面我们是从 level-1 下标开始的，为了方便编写，直接让 level 为0，这也是上面为什么是 MAX_LEVEL+1
    
    for(int i=level-1;i>=0;--i)
    {
        lst_pos[i]=lst_pos[i+1];//往下爬，但是下标不动

        while(cur->next[i]&&cur->next[i]->key<key)
            lst_pos[i]+=cur->next[i].span, //下标加上跨幅
            cur=cur->next[i]; 
        
        update[i]=cur; //需要更新span和next的点
    }

    int newlevel=random_level();//新节点生成高度

    if(newlevel>level)//如果大于现在的高度，那么需要更新
    {
        for(int i=level;i<newlevel;++i)
            update[i]=head,  //因为上面的层数只有一个新节点，所以都先设置为头结点
            update[i]->next[i].span=length, // 跨幅为length
            lst_pos[i]=0; //上一个为0，这都是在进行初始化

        level=newlevel;
    }

    cur=create_node(newlevel,key);//创建新节点，不用担心会丢失应该插入的节点的位置，因为update数组有在记录

    for(int i=0;i<newlevel;++i)
    {
        cur->next[i]=update[i]->next[i]; //这就是链表的插入语句，
        cur->next[i].span=update[i]->next[i].span-(lst_pos[0]-lst_pos[i]);
        //更新新节点跨幅，lst_pos[0]表示在第0层上一个节点的位置，lst_pos[i]表示在第i层上一个节点的位置，这样就很好理解了。

        update[i]->next[i].pointer=cur;//也是链表的插入语句
        update[i]->next[i].span=lst_pos[0]-lst_pos[i]+1;//新增一个节点，所以加1
    }

    for(int i=newlevel;i<level;++i)//处理当newlevel小于level的情况，把上层的进行加加
        ++update[i]->next[i].span;
    
    ++length;
}

void erase(const ll &key)
{
    Node*cur=head;
    Node::nodePointer update[MAX_LEVEL];

    for(int i=level-1;i>=0;--i)
    {
        while(cur->next[i]&&cur->next[i]->key<key)
            cur=cur->next[i];
        update[i]=cur;
    }

    cur=cur->next[0];//现在cur指向应该删除的节点位置。

    for(int i=0;i<level;++i)//更新跨幅和next指针
        if(update[i]->next[i]==cur)
            update[i]->next[i].span+=cur->next[i].span-1,
            update[i]->next[i].pointer=cur->next[i].pointer;
        else
            --update[i]->next[i].span;
    
    while(level>1&&!head->next[level-1])
    //这个地方注意，如果节点被删除可能会导致层数减少，层数减少的标准为head->next[level-1]==nullptr，
    //从上向下减少
        --level;
    
    del_node(cur);//删除节点。
    --length;
}

//下面两个查找，没什么好说的
int get_rank(const ll & key)
{
    Node*cur = head;
    int res=0;

    for(int i=level-1;i>=0;--i)
        while(cur->next[i]&&cur->next[i]->key<key)
            res+=cur->next[i].span,
            cur=cur->next[i];

    return res+1;
}

ll find_by_rank(int k)
{
    Node* cur=head;
    for(int i=level-1;i>=0;--i)
        while(cur->next[i]&&k-cur->next[i].span>0)
            k-=cur->next[i].span,
            cur=cur->next[i];
    return cur->next[0]->key;
}

Node* prev(const ll & key)
{
    Node*cur=head;
    for(int i=level-1;i>=0;--i)
        while(cur->next[i]&&cur->next[i]->key<key)
            cur=cur->next[i];
    return cur;
}

Node* next(const ll & key)
{
    Node*cur=head;
    for(int i=level-1;i>=0;--i)
        while(cur->next[i]&&cur->next[i]->key<=key)
            cur=cur->next[i];
    return cur->next[0];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

#ifdef LOCAL
    clock_t c1 = clock();
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif

//-------------------------------------------------

    int n,op;
    ll x;
    cin>>n;

    while(n--)
    {
        cin>>op>>x;
        switch(op)
        {
            case 1:insert(x);break;
            case 2:erase(x);break;
            case 3:cout<< get_rank(x) <<'\n';break;
            case 4:cout<< find_by_rank(x) <<'\n';break;
            case 5:cout<< prev(x)->key <<'\n';break;
            case 6:cout<< next(x)->key <<'\n';break;
        }
    }


//-------------------------------------------------

#ifdef LOCAL
    cout << "\nTime Used: \n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
