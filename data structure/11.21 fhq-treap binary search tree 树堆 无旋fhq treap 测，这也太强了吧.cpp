#include <iostream>
#include <random>
#include <algorithm>

#define ll long long

using namespace std;

//总结：合理的暴力就是优雅
//fhq-treap 利用了fix在merge中降低高度，用split提升了树的功能性
//我想让整个世界都知道这个数据结构

struct fhqTreapnode{
    fhqTreapnode *left,*right;
    int fix,key,Size;
};

class fhqTreap{
private:
    unsigned int Size;
    fhqTreapnode*root;
    bool result;

public:
    fhqTreap(){
        Size=0;
        root=new fhqTreapnode;
        root->left=root->right=root;
        root->fix=-RAND_MAX;
        root->Size=0;
        srand(233);
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

    bool insert(int val)
    {
        //分裂成两个树，x小于等于val，y大于val，
        //然后合并x和val创建的树，最后合并后两者，即可插入
        fhqTreapnode*now,*x,*y;
        newnode(now,val);
        split(root->left,val,x,y);
        now=merge(x,now);
        root->left=merge(now,y);
        return true;
    }

    bool erase(int val)
    {
        //先分裂成x小于等于val，z大于val
        //再分裂成y等于val，x小于val
        //然后准备删除y的根节点，先保存下来
        //之后合并y树根节点的两个子树
        //删除temp
        //合并x，y，z即可

        fhqTreapnode*x,*y,*z,*temp;
        split(root->left,val,x,z);
        split(x,val-1,x,y);
        temp=y;
        y=merge(y->left,y->right);

        if(temp!=root)
            delete temp;
            
        y=merge(x,y);
        root->left=merge(y,z);
        return true;
    }

    fhqTreapnode*search(int val)
    {
        //和删除，是一样的方式
        fhqTreapnode*x,*y,*z,*ans;
        split(root->left,val,x,z);
        split(x,val-1,x,y);
        ans=y;
        y=merge(x,y);
        root->left=merge(y,z);
        return (ans==root)?nullptr:ans;
    }

private:

    void newnode(fhqTreapnode*&now,int &key)
    {
        now=new fhqTreapnode;
        now->key=key;
        now->left=now->right=root;
        now->Size=1;
        now->fix=rand();
    }

    void update(fhqTreapnode*&now)//更新size
    {
        if(now==root)return;
        now->Size=now->left->Size+now->right->Size+1;
    }

    fhqTreapnode* merge(fhqTreapnode*x,fhqTreapnode*y)//合并只有之中，前提条件是，x树的所有值全都小于等于y树上的值
    {
        if(x==root)return y;
        else if(y==root)return x;
        
        //x树的值小于等于y树的值，说明y在x右边；而fix则是尽可能降低高度而已
        //可知，y在x的右下方。
        //所以，如x的fix比较大，那么y应该和x的右子树合并
        //如y的fix比较大，x应该和y的左子树合并

        if(x->fix>y->fix)//x的修正值大，但是x的值小，所以向右走
        {
            x->right=merge(x->right,y);
            update(x);
            return x;
        }
        else//y修正值小，但y的值大，所以向左走
        {
            y->left=merge(x,y->left);
            update(y);
            return y;
        }
    }

    void split(fhqTreapnode*now,int val,fhqTreapnode*&x,fhqTreapnode*&y)
    //按值分裂，一颗大于，一颗小于等于；也可以按大小分，一颗等于，一颗为全部剩余
    {
        if(now==root)
        {
            x=y=root;
            return;
        }

        //要求x树上的值全部小于等于val y树上的值全部大于val，当然可以就行修改
        if(now->key<=val)
        {
            x=now;
            split(now->right,val,x->right,y);
        }
        else
        {   
            y=now;
            split(now->left,val,x,y->left);
        }
        update(now);
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);


    fhqTreap it;
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

    // int a[n+1];

    // for(int i=1;i<=n;++i)
    // {
    //     cin>>a[i];
    //     it.insert(a[i]);
    // }

    // sort(a+1,a+1+n);

    // for(int i=1;i<=n;++i)
    // {
    //     auto res=it.search(a[i]);

    //     if(res!=nullptr)
    //         cout<<res->key<<' ';
    //     it.erase(a[i]);
    // }
    cout<<endl;
    system("pause");
    return 0;
}
