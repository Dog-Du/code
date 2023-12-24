#include <iostream>
#include <algorithm>
#include <random>

#define ll long long

using namespace std;

//要求key大于左子树，小于右子树，fix大于两者
//思想：key的性质由二叉排序树保证，fix由旋转保证，而由fix引起的旋转保证了树的高度较低水平
//方法：左孩子fix大，右旋，右孩子fix大，左旋。很简单吧，删除的时候直接寻找继任者，根本不需要旋转

struct Treapnode{
    int key,fix,Size;
    Treapnode*left,*right;
};

class Treap{
private:
    Treapnode*root;
    unsigned int Size;
    bool result;

public:
    Treap(){
        root=new Treapnode;
        root->left=root->right=root;//空指针全部指向头结点
        root->fix=-RAND_MAX;//把头结点置为最小值
        root->Size=0;
        srand(114514);//随机化
    }

    bool insert(int x)
    {
        result=false;
        insert(root->left,x);
        return result;
    }

    bool erase(int x)
    {
        result=false;
        erase(root->left,x);
        return result;
    }

    Treapnode*search(int x)
    {
        auto*p=root->left,*q=root;

        while(p!=root)
        {
            if(p->key==x)return p;
            q=p;
            if(p->key>x)p=p->left;
            else p=p->right;
        }

        return nullptr;
    }

    int get_rank(int x)
    {
        auto*now=root->left;
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
    int get_val(int rank)
    {
        auto*now=root->left;

        while(now!=root&&now!=nullptr)
        {
            if(now->left->Size+1==rank)
                break;
            else if(now->left->Size>=rank)
                now=now->left;
            else
            {
                rank-=now->left->Size+1;
                now=now->right;
            }
        }

        return now->key;
    }
    int get_pre(int x)
    {
        auto*p=root->left;
        int pre;

        while(p!=root&&p!=nullptr)
        {
            if(p->key<x)pre=p->key,p=p->right;
            else p=p->left;
        }

        return pre;
    }

    int get_next(int x)
    {
        auto*p=root->left;
        int next;

        while(p!=root&&p!=nullptr)
        {
            if(p->key>x)next=p->key,p=p->left;
            else p=p->right;
        }

        return next;
    }

private:

    void update(Treapnode*now)
    {
        if(now==root)return;
        now->Size=now->left->Size+now->right->Size+1;
    }

    void SuccessOr(Treapnode*&now,int&key)//寻找继任者，赋值，之后移除
    {
        if(now->right==root)
        {
            Treapnode*temp=now;
            now=now->left;//注意写法，这是引用型参数的意义
            key=move(temp->key);
            delete temp;
            return;
        }

        SuccessOr(now->right,key);

        update(now);//更新Size即可，不需要旋转
    }

    void erase(Treapnode*&now,int &key)//删除函数中，从头至尾根本不需要旋转
    {
        if(now==root)
        {
            result=false;
            return;
        }
        else if(now->key>key)erase(now->left,key);
        else if(now->key<key)erase(now->right,key);
        else
        {
            if(now->left==root)
            {
                Treapnode*temp=now;
                now=now->right;
                delete temp;
                return;
            }
            else if(now->right==root)
            {
                Treapnode*temp=now;
                now=now->left;
                delete temp;
                return;
            }
            else
            {
                SuccessOr(now->left,now->key);
            }
        }

        update(now);
        return;
    }

    void insert(Treapnode*&now,int &key)//只有插入时需要旋转
    {
        if(now==root)
        {
            now=new Treapnode;
            now->fix=rand()+RAND_MAX;//避免为负数
            now->left=now->right=root;
            now->key=key;
            now->Size=1;
            result=true;
            return;
        }
        else if(now->key>key)insert(now->left,key);
        else insert(now->right,key);//允许重复插入

        check(now);//检查，并更新Size
    }

    void check(Treapnode*&now)
    {
        if(now->fix<now->left->fix)//左孩子大，右旋
            Rrotate(now);
        else if(now->fix<now->right->fix)//右孩子大，左旋
            Lrotate(now);
        else
            update(now);//不然更新Size，
    }

    void Rrotate(Treapnode*&now)
    {
        Treapnode*left=now->left;
        now->left=left->right;
        left->right=now;
        now=left;
        update(now->right),update(now);
    }

    void Lrotate(Treapnode*&now)
    {
        Treapnode*right=now->right;
        now->right=right->left;
        right->left=now;
        now=right;
        update(now->left),update(now);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    Treap it;
    int n;
    cin>>n;

    while(n--)
    {
        int op,x;
        cin>>op>>x;

        if(op==1)
        {
            it.insert(x);
        }
        else if(op==2)
        {
            it.erase(x);
        }
        else if(op==3)
        {
            cout<<it.get_rank(x)<<'\n';
        }
        else if(op==4)
        {
            cout<<it.get_val(x)<<'\n';
        }
        else if(op==5)
        {
            cout<<it.get_pre(x)<<'\n';
        }
        else if(op==6)
        {
            cout<<it.get_next(x)<<'\n';
        }
        else if(op==7)
        {
            cout<<it.search(x)->key<<endl;
        }
        
    } 
    cout<<endl;
    system("pause");
    return 0;
}
