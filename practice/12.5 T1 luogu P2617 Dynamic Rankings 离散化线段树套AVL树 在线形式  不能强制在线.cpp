#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

const int maxn=2e5;

//如果使用Treap会超时，因为常数比较大，选用AVL树效率是最高的。
//单次修改与单次修改时间复杂度 logn的平方

//在值域上建立线段树，每个节点用平衡树维护下标即可。

struct AVLnode{
    AVLnode*left,*right;
    int height,Size;
    int key;
};

class AVLTree{
private:
    int Size=0;
    AVLnode*root;
public:
    AVLTree(){
        root=new AVLnode;
        Size=0;
        root->left=nullptr;
        root->right=nullptr;
        root->height=0;
        root->Size=0;
    }

    bool insert(int x)
    {
        bool flag;
        ins(root->left,x,flag);
        return flag;
    }
    bool erase(int x)
    {
        bool flag;
        del(root->left,x,flag);
        return flag;
    }
    AVLnode*search(int x)
    {
        AVLnode*ans;
        _search(root->left,x,ans);
        return ans;
    }

    int get_rank(int x)
    {
        AVLnode*now=root->left;
        int rank=1;

        while(now!=root&&now!=nullptr)
        {
            if(x<=now->key)
                now=now->left;
            else
            {
                rank+=now->left->Size+1;
                now=now->right;
            }
        }

        return rank;
    }

    int upper_bound(int x)
    {
        AVLnode*now=root->left;
        int rank=1;

        while(now!=root&&now!=nullptr)
        {
            if(x<now->key)
                now=now->left;
            else
            {
                rank+=now->left->Size+1;
                now=now->right;
            }
        }

        return rank;
    }
private:

    void del(AVLnode*&now,int&key,bool&flag)
    {
        if(now==root||now==nullptr)
        {
            flag=0;
            return;
        }
        else if(key>now->key)del(now->right,key,flag);
        else if(key<now->key)del(now->left,key,flag);
        else
        {
            AVLnode*temp=now,*l=now->left,*r=now->right;

            if(l==root)now=r;
            else if(r==root)now=l;
            else
            {
                now=find(l,l);//把这个节点剖下来

                if(now!=l)//如果不是直接为左边的
                    now->left=l;

                now->right=r;
            }

            --Size;
            flag=1;
            delete temp;
        }

        if(flag)
            check(now);
        return;
    }

    AVLnode* find(AVLnode*&now,AVLnode*fa)
    {
        AVLnode*res;

        if(now->right==root)
        {
            res=now;
            fa->right=now->left;
        }
        else
        {
            res=find(now->right,now);
            check(now);
        }

        return res;
    }

    void _search(AVLnode*&now,int &key,AVLnode*&ans)
    {
        if(now==root||now==nullptr)
        {
            ans=nullptr;
            return;
        }
        else if(key>now->key)_search(now->right,key,ans);
        else if(key<now->key)_search(now->left,key,ans);
        else
        {
            ans=now;
            return;
        }

    }

    void ins(AVLnode*&now,int& key,bool &flag)
    {
        if(now==root||now==nullptr)
        {
            newnode(now,key);
            flag=1;
        }
        else if(key>now->key)ins(now->right,key,flag);
        else ins(now->left,key,flag);

        if(flag)
            check(now);
    }

    void check(AVLnode*&T)
    {
        int bf=factor(T);

        if(bf>1)
        {
            int lf=factor(T->left);
            if(lf>=0)Rrotate(T);
            else Lrotate(T->left),Rrotate(T);

        }
        else if(bf<-1)
        {
            int rf=factor(T->right);
            if(rf<=0)Lrotate(T);
            else Rrotate(T->right),Lrotate(T);
        }
        else if(T!=root)update(T);
    }

    int factor(AVLnode*&T)
    {
        if(T==root)return 0;
        return T->left->height-T->right->height;
    }
    
    void Rrotate(AVLnode*&T)
    {
        AVLnode*L=T->left;
        T->left=L->right;
        L->right=T;
        T=L;
        update(T->right),update(T);
    }
    void Lrotate(AVLnode*&T)
    {
        AVLnode*R=T->right;
        T->right=R->left;
        R->left=T;
        T=R;
        update(T->left),update(T);
    }
    void update(AVLnode*&T)
    {
        if(T==root)return;
        T->height=max(T->left->height,T->right->height)+1;
        T->Size=T->left->Size+T->right->Size+1;
    }
    void newnode(AVLnode*&T,int &key)
    {
        T=new AVLnode;
        T->left=T->right=root;
        T->height=1;
        T->key=key;
        ++Size;
    }
};

AVLTree t[maxn<<2];//这个是树

struct Q{
    char ch;
    int x,y,k;
}q[maxn];//这个是问题集合

int tot=0;//表的长度
int b[maxn<<1];//这个是用来查找的表
int a[maxn];//a是原数组

int n,m,l,r,k,ans,x,y;

void insert(int now,int l,int r)
{
    if(l==r)
    {
        t[now].insert(y);
        return;
    }

    int mid=l+r>>1;
    if(mid>=x)insert(now<<1,l,mid);
    else insert(now<<1|1,mid+1,r);
    t[now].insert(y);
}

void erase(int now,int l,int r)
{
    if(l==r)
    {
        t[now].erase(y);
        return;
    }
    int mid=l+r>>1;
    if(mid>=x)erase(now<<1,l,mid);
    else erase(now<<1|1,mid+1,r);
    t[now].erase(y);
}

//问左子树多少个数字的id在L，R之间，如果大于k，去左子树，如果小于k，去右子树，如果k等于0，那么得到答案
void query(int x,int l,int r,int L,int R,int k)
{
    if(l==r)
    {
        ans=b[l];
        return;
    }

    int left=x<<1;
    int cntl=t[left].get_rank(L);
    int cntr=t[left].upper_bound(R)-1;

    int mid=l+r>>1;

    if(cntr-cntl+1>=k)query(x<<1,l,mid,L,R,k);
    else query(x<<1|1,mid+1,r,L,R,k-(cntr-cntl+1));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    // fstream fin;
    // fin.open("E:\\DOWNLOAD\\P2617_11 (1).in");

    // fin>>n>>m;

    cin>>n>>m;

    for(int i=1;i<=n;++i)
    {
        //fin>>a[i].val;
        cin>>a[i];
        b[++tot]=a[i];
    }

    for(int i=1;i<=m;++i)
    {
        //fin>>q[i].ch;
        cin>>q[i].ch;
        if(q[i].ch=='Q')
            //fin>>q[i].x>>q[i].y>>q[i].k;
            cin>>q[i].x>>q[i].y>>q[i].k;
        else
        {
            //fin>>q[i].x>>q[i].y;
            cin>>q[i].x>>q[i].y;
            b[++tot]=q[i].y;
        }
    }

    sort(b+1,b+tot+1);
    tot=unique(b+1,b+tot+1)-b-1;

    for(int i=1;i<=n;++i)
    {
        y=i;
        x=lower_bound(b+1,b+1+tot,a[i])-b;
        insert(1,1,tot);
    }


    for(int i=1;i<=m;++i)
    {
        if(q[i].ch=='Q')
        {
            query(1,1,tot,q[i].x,q[i].y,q[i].k);
            cout<<ans<<'\n';
        }
        else
        {
            //修改=先删除，再插入。
            //先得到原来这个点的数的离散值
            x=lower_bound(b+1,b+1+tot,a[q[i].x])-b;//位置
            y=q[i].x;//下标，
            erase(1,1,tot);//删除
            a[q[i].x]=q[i].y;//然后修改原数组的值，方便下一次查找
            x=lower_bound(b+1,b+1+tot,q[i].y)-b;//位置
            y=q[i].x;//下标
            insert(1,1,tot);//插入。
        }
    }

    cout<<endl;
    system("pause");
    return 0;
}
