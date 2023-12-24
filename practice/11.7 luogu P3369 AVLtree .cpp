#include <iostream>

using namespace std;

//删去了value,允许重复插入，方便处理get_val函数

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

    int get_val(int rank)
    {
        AVLnode*now=root->left;

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
        AVLnode*p=root->left;
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
        AVLnode*p=root->left;
        int next;

        while(p!=root&&p!=nullptr)
        {
            if(p->key>x)next=p->key,p=p->left;
            else p=p->right;
        }

        return next;
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
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    int n;
    cin>>n;
    AVLTree it;

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
            int t=it.get_rank(x)-1;
            cout<<it.get_val(t)<<'\n';
        }
        else if(op==6)
        {
            int t=it.get_rank(x+1);
            cout<<it.get_val(t)<<'\n';
        }
    }

    cout<<endl;
    system("pause");
    return 0;
}
