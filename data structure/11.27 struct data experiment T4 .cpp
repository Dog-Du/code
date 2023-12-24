#include <iostream>
#include <vector>

#define ll long long

using namespace std;
  
//AVL树 作用：实现删除，插入，查询，两个树合并，

struct AVLnode{
    int key,value,height;
    AVLnode*left,*right;
};

class AVLTree{
private:
    AVLnode*root;//头结点，所有空指针全部指向root
    bool changed;

public:
    AVLTree(){
        root=new AVLnode;
        root->left=root->right=root;
        root->height=0;
        //用于在merge函数中区分空指针
        root->key=RAND_MAX;
        root->value=-RAND_MAX;
    }

    AVLnode*search(int x)
    {
        AVLnode*now=root->left;

        while(now!=root)
        {
            if(now->key==x)return now;
            
            if(now->key>x)now=now->left;
            else now=now->right;
        }

        return nullptr;
    }

    bool insert(int key,int value)//返回true表示新key，返回false表示覆盖
    {
        changed=false;
        insert(root->left,key,value);
        return changed;
    }

    bool erase(int key)//返回true表示删除成功，不然不存在key
    {
        changed=false;
        erase(root->left,key);
        return changed;
    }

    AVLnode* getroot()//返回根，仅用于merge
    {
        if(root->left==root)return nullptr;
        return root->left;
    }

    void merge(AVLnode*it)//暴力合并，允许key值有重叠，那样会直接覆盖 mlog(n+m)
    {
        if(it->key==RAND_MAX&&it->value==-RAND_MAX)
            return;
        insert(it->key,it->value);
        merge(it->left);
        merge(it->right);
    }

    void show()//前序遍历打印
    {
        show(root->left);
    }

private:

    void show(AVLnode*now)
    {
        if(now==root)return;
        cout<< now->key <<":"<<now->value<<"->";
        show(now->left);
        show(now->right);
    }

    void SuccessOr(AVLnode*&now,AVLnode*fa)//找前驱
    {
        if(now->right==root)
        {
            AVLnode*temp=now;
            now=now->left;//替代
            fa->key=temp->key;
            fa->value=temp->value;
            delete temp;
            return;
        }
        
        SuccessOr(now->right,fa);
        check(now);
        return;
    }

    void erase(AVLnode*&now,int&key)
    {
        if(now==root)
        {
            changed=false;
            return;
        }
        else if(now->key>key)erase(now->left,key);
        else if(now->key<key)erase(now->right,key);
        else
        {
            changed=true;
            if(now->left==root)
            {
                AVLnode*temp=now;
                now=now->right;
                delete temp;
                return;
            }
            else if(now->right==root)
            {
                AVLnode*temp=now;
                now=now->left;
                delete temp;
                return;
            }
            else
            {
                SuccessOr(now->left,now);
            }
        }

        check(now);
    }

    void check(AVLnode*&now)//检查
    {
        int nowbf=factor(now);

        if(nowbf>1)
        {
            int leftbf=factor(now->left);
            if(leftbf==-1)Lrotate(now->left),Rrotate(now);//LRLR
            else Rrotate(now);//LLR
        }
        else if(nowbf<-1)
        {
            int rightbf=factor(now->right);
            if(rightbf==1)Rrotate(now->right),Lrotate(now);//RLRL
            else Lrotate(now);//RRL
        }
        else
            update(now);
    }

    int factor(AVLnode*now)
    {
        if(now==root)return 0;
        return now->left->height-now->right->height;
    }

    void insert(AVLnode*&now,int &key,int &value)
    {
        if(now==root)
        {
            now=new AVLnode;
            now->key=key;
            now->value=value;
            now->height=1;
            now->left=now->right=root;
            changed=true;
            return;
        }
        else if(now->key>key)insert(now->left,key,value);
        else if(now->key<key)insert(now->right,key,value);
        else
        {
            changed=false;
            now->value=value;
            return;
        }

        check(now);
    }

    void update(AVLnode*&now)
    {
        if(now==root)return;
        now->height=max(now->left->height,now->right->height)+1;
    }

    void Lrotate(AVLnode*&now)
    {
        AVLnode*right=now->right;
        now->right=right->left;
        right->left=now;
        now=right;
        update(now->left),update(now);
    }

    void Rrotate(AVLnode*&now)
    {
        AVLnode*left=now->left;
        now->left=left->right;
        left->right=now;
        now=left;
        update(now->right),update(now);
    }
};

vector<AVLTree> root;

int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0),cout.tie(0);

    int t,x,y,z,op;
    cin>>t;

    //root.resize(1);

    //第一个表示操作，第二个是树的序号，第三个是key，第四个是value
    while(t--)
    {
        cin>>op>>x;
        if(op==1)//插入
        {
            cin>>y>>z;
            bool flag=root[x].insert(y,z);
            
            if(flag)cout<<"insert finished"<<endl;
            else cout<<"key refresh"<<endl;
        }
        else if(op==2)//删除
        {
            cin>>y;
            bool flag=root[x].erase(y);
            
            if(flag)cout<<"erase finished"<<endl;
            else cout<<"not have this key"<<endl;
        }
        else if(op==3)//查询
        {
            cin>>y;
            AVLnode*res=root[x].search(y);

            if(res==nullptr)cout<<"empty"<<endl;
            else cout<<"key:"<<res->key<<" value:"<<res->value<<endl;
        }
        else if(op==4)//合并
        {
            cin>>y;
            root[x].merge(root[y].getroot());
        }
        else if(op==5)//创建
        {
            AVLTree it;
            root.push_back(it);
            cout<<"new root builded , it called "<< root.size() - 1 << endl;
        }
        else if(op==6)//前序遍历
        {
            root[x].show();
        }
    }

    cout<<endl;
    system("pause");
    return 0;
}
