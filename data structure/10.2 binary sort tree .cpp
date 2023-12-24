#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

typedef struct {
    int key;
    int otherkey;

}ElemType;

typedef struct BSTNode{
    int data;
    BSTNode* l,*r;

    BSTNode(){
        l=nullptr,r=nullptr;
    }

    void erase(BSTNode*&root,int x)//传入的是头结点，而不是首节点
    {
        BSTNode*p=root->l,*f=root,*s;//f指向p的双亲

        while(p!=nullptr)//寻找x
        {
            if(p->data==x)break;
            f=p;

            if(x>p->data)p=p->r;
            else p=p->l;
        }

        if(p==nullptr)return;//x不在，返回

        if(p->l!=nullptr&&p->r!=nullptr)//三种情况讨论，如果左右都不为空
        {
            //s指向q双亲
            BSTNode*q=p->l;
            s=p;

            //q只找p的左子树中的最大值
            while(q->r!=nullptr)
            {
                s=q,q=q->r;
            }

            //先把s指向q的部分置空，防止s=q
            if(s->l==q)s->l=nullptr;
            else s->r=nullptr;

            //q赋值p
            q->l=p->l;
            q->r=p->r;

            //把f指向p的部分指向q
            if(f->l==p)f->l=q;
            else f->r=q;

            delete p;//删除节点

            return;
        }
        else if(p->l==nullptr)
        {
            s=p->r;
        }
        else if(p->r==nullptr)
        {
            s=p->l;
        }

        if(f==nullptr)root=p;
        else if(f->l==p)f->l=s;
        else f->r=s;

        delete p;

        return;
    }

    void inert(BSTNode*&root,int x)//递归写法，传入的需要是首节点而不是头结点
    {
        if(root==nullptr)
        {
            root=new BSTNode;
            root->data=x;
            return;
        }

        if(x>root->data)inert(root->r,x);
        else if(x<root->data) inert(root->l,x);
    }

    void insert(BSTNode* &root,int x)//非递归写法，传入的需要是头结点而不是首节点
    {
        //在树中没有key x的时候再插入
        if(root->l==nullptr)
        {
            root->l=new BSTNode;
            root->l->data=x;
            return;
        }
        
        BSTNode*p=root->l,*f=root;

        while(p!=nullptr)
        {
            if(p->data==x)break;

            f=p;

            if(x>p->data)p=p->r;
            else p=p->l;
        }

        if(p==nullptr)
        {
            if(x>f->data)
            {
                f->r=new BSTNode;
                f->r->data=x;
            }
            else
            {
                f->l=new BSTNode;
                f->l->data=x;
            }
        }
    }

    // BSTNode * search(BSTNode*root,int x)//递归写法
    // {
    //     if(root==nullptr)return nullptr;
    //     if(x==root->data)return root;

    //     if(x>root->data)return search(root->r,x);
    //     if(x<root->data)return search(root->l,x);
    // }

    BSTNode*search(BSTNode*root,int x)//非递归写法,
    {
        auto p=root->l;

        while(p!=nullptr)
        {
            if(p->data==x)return p;
            
            if(x>p->data)p=p->r;
            else p=p->l;
        }

        return nullptr;
    }

}*BSTree;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    BSTree  tree= new BSTNode;
        
    int t;
    cin>>t;

    while(t--)
    {
        int op,x;

        cin>>op>>x;

        if(op==1)
        {
            auto p=tree->search(tree,x);
            if(p==nullptr)cout<<"empty"<<endl;
            else cout<<p->data<<endl;
        }
        else if(op==2)
        {
            tree->insert(tree,x);
        }
        else if(op==3)
        {
            tree->erase(tree,x);
        }
    }

    cout<<endl;
    system("pause");
    return 0;
}
