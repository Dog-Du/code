#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

struct AVLnode{
    AVLnode*left,*right;
    int height;
    int key,value;
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
        else if(key<now->key)ins(now->left,key,flag);
        else
        {
            flag=0;
            ++now->value;
            return;
        }

        if(flag)
            check(now);
    }

    void check(AVLnode*&T)
    {
        int bf=factor(T);

        if(bf>1)
        {
            int lf=factor(T->left);
            if(lf>0)Rrotate(T);
            else Lrotate(T->left),Rrotate(T);

        }
        else if(bf<-1)
        {
            int rf=factor(T->right);
            if(rf<0)Lrotate(T);
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
    }
    void newnode(AVLnode*&T,int &key)
    {
        T=new AVLnode;
        T->left=T->right=root;
        T->height=1;
        T->key=key;
        T->value=1;
        ++Size;
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    int n;
    cin>>n;
    int a[n+1];
    AVLTree it;

    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
        it.insert(a[i]);
    }

    sort(a+1,a+1+n);
    int tot=unique(a+1,a+1+n)-a-1;

    for(int i=1;i<=tot;++i)
    {
        AVLnode *res=it.search(a[i]);
        while(res->value--)cout<<res->key<<' ';
        it.erase(a[i]);
    }

    cout<<endl;
    system("pause");
    return 0;
}
