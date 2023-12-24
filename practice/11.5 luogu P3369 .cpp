#include <iostream>
#include <algorithm>
using namespace std;

//根据竞赛式改成指针式，成功！为我喝彩！

struct AVLNode{
    AVLNode*left,*right;//没有parent，所以需要递归，因为递归，所以简单
    int key,value;
    int height;//因为bf可以由height算出，所以存height
    int size;
};

class AVLTree{
private:
    AVLNode* tree;//所有空指针全部指向tree，方便更新高度和计算平衡因子
    int Size;

public:
    AVLTree(){
        tree=new AVLNode;
        tree->height=0;//设置成0
        tree->left=nullptr;//置空，方便处理第一个元素
        tree->right=nullptr;
        tree->size=0;
        Size=0;
    }

    bool insert(int x)//false有元素，并value+1
    {
        return ins(tree->left,x);
    }

    bool erase(int x)//true无元素
    {
        return del(tree->left,x);
    }

    AVLNode* search(int x)//返回指针
    {
        return Search(tree->left,x);
    }

    int findrear(int x)
    {
        AVLNode*f=tree,*p=tree->left;

        while(p!=nullptr)
        {
            if(p->key<x)f=p,p=p->left;
            else p=p->right;
        }

        return f->key;
    }

    int findpre(int x)
    {
        AVLNode*f=tree,*p=tree->left;

        while(p!=nullptr)
        {
            if(p->key<x)f=p,p=p->right;
            else p=p->left;
        }

        return f->key;
    }

    int paiming(int x)
    {
        return paiming(tree->left,x);
    }

private:

    int paiming(AVLNode*&root,int &x)
    {
        if(x==0)return root->key;
        else if(x>=root->size)return paiming(root->right,x-=root->size);
        else if(x<root->size)return paiming(root->left,x);
    }

    AVLNode* Search(AVLNode*&T,int &key)//查找
    {
        if(T==tree)return nullptr;//如果找到tree，查找失败，返回空
        else if(key>T->key)return Search(T->right,key);
        else if(key<T->key)return Search(T->left,key);
        else return T;
    }

    bool del(AVLNode*&T,int &key)//删除
    {
        if(T==tree)return false;//如果tree，查找失败，返回false

        bool flag=false;//保存结果，防止影响check

        if(key<T->key)flag=del(T->left,key);
        else if(key>T->key)flag=del(T->right,key);
        else
        {
            if(--T->value>0)
            {
                return false;
            }

            AVLNode*l=T->left,*r=T->right;

            AVLNode* temp=T;//保存T节点，之后释放

            if(l==tree)T=r;//左或右为空，直接更改，因为是height存bf，不用改bf，之后直接check就好了
            else if(r==tree)T=l;
            else
            {
                T=find(r,r);//找直接后继
                if(T!=r)
                    T->right=r;
                T->left=l;   
            }
            
            delete temp;//释放

            --Size;
            flag=true;
        }
        

        check(T);//一路check

        return flag;
    }

    AVLNode* find(AVLNode*&T,AVLNode* fa)//找直接后继
    {
        AVLNode*res;

        if(T->left==tree)//找到了直接后继
        {
            res=T;//返回直接后继
            fa->left=T->right;//把父节点的左边置为它的右边
        }
        else
        {
            res=find(T->left,T);//递归查找
            check(T);//高度改变，check
        }

        return res;
    }

    bool ins(AVLNode*&T,int &key)//插入
    {
        bool flag=false;

        if(T==tree||T==nullptr)//空，则new
        {
            newnode(T,key);
            flag=true;
        }
        else if(key<T->key)flag=ins(T->left,key);
        else if(key>T->key)flag=ins(T->right,key);
        else
        {
            ++T->value;
            flag=false;
        }

        check(T);

        return flag;
    }

    void newnode(AVLNode*&p,int& val)
    {
        p=new AVLNode;
        p->key=val;
        p->value=1;
        p->left=p->right=tree;//指向tree
        p->height=1;
        p->size=1;
        ++Size;
    }

    void update(AVLNode*&p)//更新高度
    {
        if(p==tree)return;//如果是tree，不更新高度，一直为0
        p->height=max(p->left->height,p->right->height)+1;
        p->size=p->left->size+p->right->size+1;
    }

    int factor(AVLNode*&p)//获得bf
    {
        if(p==tree)return 0;
        return p->left->height-p->right->height;//返回因子
    }

    void lrotate(AVLNode*&T)//左旋
    {
        AVLNode*r=T->right;
        T->right=r->left;
        r->left=T;
        T=r;

        update(T->left),update(T);
    }

    void rrotate(AVLNode*&T)//右旋
    {
        AVLNode*l=T->left;
        T->left=l->right;
        l->right=T;
        T=l;

        update(T->right),update(T);
    }

    void check(AVLNode*&T)//check
    {
        int bf=factor(T);//获得因子

        if(bf>1)
        {
            int lf=factor(T->left);

            if(lf>0)rrotate(T);
            else lrotate(T->left),rrotate(T);
        }
        else if(bf<-1)
        {
            int rf=factor(T->right);

            if(rf<0)lrotate(T);
            else rrotate(T->right),lrotate(T);
        }
        else if(T!=tree)update(T);//如果平衡，并且非空，更新高度
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    AVLTree it;

    int n;
    cin>>n;

    while(n--)
    {
        int op,x;
        cin>>op>>x;

        if(op==1)it.insert(x);
        else if(op==2)it.erase(x);
        else if(op==3)cout<<it.paiming(x)-1<<endl;
        else if(op==5)cout<<it.findpre(x)<<endl;
        else if(op==4)cout<<
    }

    cout<<endl;
    system("pause");
    return 0;
}
