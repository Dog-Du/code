#include <iostream>
#include <random>
#include <ctime>

#define ll long long

using std::cin;
using std::cout;

std::random_device seed;
std::minstd_rand rng(seed());

const int MAX_LEVEL = 7;
const int N=1e5+10;

struct Node{
    int level;
    ll key;

    struct ptr{
        Node* pointer;
        int span;//跨度，用来解决get_rank和get_val

        ptr():pointer(nullptr),span(0){}
        ptr(Node*x):pointer(x),span(0){}

        operator Node*() const &{return pointer;}
        Node* operator->() const&{return pointer;}
    }nxt[MAX_LEVEL];
}space[N],*rubbin[N];

Node* tot =space;
Node*head=space;
int bintop;

//实现自己的垃圾回收，利用栈，以后可以学习一下。
#define new_node() (bintop?rubbin[bintop--]:++tot)
#define del_node(x) (rubbin[++bintop]=(x))

int level;//global max level now
int length;

int random_level()
{
    int res=1;
    while(res<MAX_LEVEL&&(rng()&1)&&(rng()&1))
        ++res;
    return res;
}

Node* create_node(const int &level,const ll & key)
{
    Node*res=new_node();
    res->key=key;
    res->level=level;
    return res;
}

void insert(const ll &key)
{
    Node* cur=head;
    Node::ptr update[MAX_LEVEL];

    int lst_pos[MAX_LEVEL+1];
    lst_pos[level]=0;

    for(int l=level-1;l>-1;--l)
    {
        lst_pos[l]=lst_pos[l+1];

        while(cur->nxt[l]&&cur->nxt[l]->key < key)
        {
            lst_pos[l]+=cur->nxt[l].span;
            cur=cur->nxt[l];
        }
        update[l]=cur;
    }

    int lev=random_level();

    if(lev>level)
    {
        for(int i=level;i<lev;++i)
        {
            update[i]=head;
            update[i]->nxt[i].span=length;
            lst_pos[i]=0;
        }
        level=lev;
    }

    cur=create_node(lev,key);

    for(int i=0;i<lev;++i)
    {
        cur->nxt[i]=update[i]->nxt[i];
        cur->nxt[i].span=update[i]->nxt[i].span-(lst_pos[0]-lst_pos[i]);
        update[i]->nxt[i].pointer=cur;
        update[i]->nxt[i].span=lst_pos[0]-lst_pos[i]+1;
    }

    for(int i=lev;i<level;++i)
        ++update[i]->nxt[i].span;
    
    ++length;
}

void erase(const ll & key)
{
    Node* cur=head; 
    Node::ptr update[MAX_LEVEL];

    for(int l=level-1;l>-1;--l)
    {
        while(cur->nxt[l]&&cur->nxt[l]->key < key)
            cur=cur->nxt[l];
        update[l]=cur;
    }

    cur=cur->nxt[0];

    for(int i=0;i<level;++i)
    {
        if(update[i]->nxt[i]==cur)
            update[i]->nxt[i].span+=cur->nxt[i].span-1,
            update[i]->nxt[i].pointer=cur->nxt[i].pointer;
        else
            --update[i]->nxt[i].span;
    }

    while(level>1&&head->nxt[level-1]==0)
        --level;
    
    del_node(cur);

    --length;
}

int get_rank(const ll & key)
{
    Node*cur=head;
    int res=0;

    for(int l=level-1;l>-1;--l)
    {
        while(cur->nxt[l]&&cur->nxt[l]->key < key)
            res+=cur->nxt[l].span,
            cur=cur->nxt[l];
    }
    return res+1;
}

ll get_val(int k)
{
    Node*cur=head;

    for(int l=level-1;l>-1;--l)
    {
        while(cur->nxt[l]&&k-cur->nxt[l].span>0)
            k-=cur->nxt[l].span,
            cur=cur->nxt[l];
    }
    return cur->nxt[0]->key;
}

Node* prev(const ll & key)
{
    Node* cur=head;
    for(int l=level-1;l>-1;--l)
    {
        while(cur->nxt[l]&&cur->nxt[l]->key < key)
            cur=cur->nxt[l];
    }
    return cur;
}

Node* next(const ll & key)
{
    Node* cur=head;
    for(int l=level-1;l>-1;--l)
    {
        while(cur->nxt[l]&&cur->nxt[l]->key <= key)
            cur=cur->nxt[l];
    }
    return cur->nxt[0];
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

#ifdef LOCAL
    clock_t c1 = clock();
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif

//-------------------------------------------------

    int n,op,x;

    cin>>n;

    while(n--)
    {
        cin>>op>>x;

        switch(op)
        {
            case 1:insert(x);break;
            case 2:erase(x);break;
            case 3:cout<<get_rank(x)<<'\n';break;
            case 4:cout<<get_val(x)<<'\n';break;
            case 5:cout<<prev(x)->key<<'\n';break;
            case 6:cout<<next(x)->key<<'\n';break;
        }
    }


//-------------------------------------------------

#ifdef LOCAL
    cout << "\nTime Used: \n" << clock() - c1 << " ms" << std::endl;
#endif

    //system("pause");
    return 0;
}
