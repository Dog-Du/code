#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

const bool black = 1;
const bool red = 0;

struct RBnode
{
    RBnode *left, *right;
    int key, Size;
    bool color;
    RBnode(int x) : key(x), Size(1), color(red) {}
};

class RBTree
{
private:
    unsigned int Size;
    RBnode *root,*double_black;
    bool reslut;

public:
    bool IsBalance()
    {
        RBnode *root = this->root->left;
        if (root->color == red)
        {
            cout << "black" << endl; // 为了测试
            return false;
        }
        // 最左路径黑色结点数量做基准值
        int banchmark = 0; // 保存最左侧路径中黑色结点的个数
        auto left = root;

        while (left != this->root)
        {
            if (left->color == black)
                ++banchmark;
            left = left->left;
        }

        int blackNum = 0; // 递归遍历时记录黑色结点的个数
        return _IsBalance(root, this->root, banchmark, blackNum);
    }

    bool _IsBalance(RBnode *root, RBnode *parent, int banchmark, int blackNum)
    {
        // 走到null之后，判断banchmark和blackNum是否相等
        if (root == this->root)
        {
            if (banchmark != blackNum)
            {
                cout << "black not" << endl; // 为了测试
                return false;
            }
            return true;
        }
        if (root->color == red && parent->color == red)
        {
            cout << "red not" << endl; // 为了测试
            return false;
        }
        if (root->color == black) // 统计黑色节点的个数
        {
            ++blackNum;
        }
        return _IsBalance(root->left, root, banchmark, blackNum) && _IsBalance(root->right, root, banchmark, blackNum);
    }

    RBTree()
    {
        root = new RBnode(0);
        // 设置一个头结点，同时把所有空指针全部指向头结点。
        // 头结点设置为黑，这与红黑树定义中的叶子结点为黑色是一致的。
        root->color = black;
        root->left = root->right = root; // 为了全部都指向头结点
        root->Size = 0;
        double_black=nullptr;
        Size = 0;
    }

    bool insert(int x)
    {
        reslut = false;
        insert(root->left, x);
        root->left->color = black;
        return reslut;
    }

    RBnode *search(int x)
    {
        return search(root->left, x);
    }

    bool erase(int x)
    {
        reslut=false;
        double_black=nullptr;
        erase(root->left,x);
        root->left->color=black;
        return reslut;
    }

    int get_rank(int x)
    {
        RBnode*now=root->left;
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
        RBnode*now=root->left;

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
        RBnode*p=root->left;
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
        RBnode*p=root->left;
        int next;

        while(p!=root&&p!=nullptr)
        {
            if(p->key>x)next=p->key,p=p->left;
            else p=p->right;
        }

        return next;
    }
private:
    bool erase_maintain(RBnode*&now)
    {
        update(now);
        if(double_black==nullptr)return false;
        else if(now->left==double_black)
        {
            double_black=nullptr;

            if(now->right->color==red)
            {
                now->right->color=black;
                now->color=red;
                Lrotate(now);
                double_black=now->left->left;
                return erase_maintain(now->left);
            }

            if(hasRedChild(now->right))
            {
                bool color=now->color;
                if(now->right->left->color==red)
                    Rrotate(now->right);
                Lrotate(now);
                now->color=color;
                now->left->color=now->right->color=black;
                return false;
            }
            else if(now->color==red)
            {
                now->color=black;
                now->right->color=red;
                return false;
            }
            else if(now->color==black)
            {
                now->right->color=red;
                double_black=now;
                return true;
            }
        }
        else if(now->right==double_black)
        {
            double_black=nullptr;

            if(now->left->color==red)
            {
                now->left->color=black;
                now->color=red;
                Rrotate(now);
                double_black=now->right->right;
                return erase_maintain(now->right);
            }

            if(hasRedChild(now->left))
            {
                bool color=now->color;
                if(now->left->right->color==red)
                    Lrotate(now->left);
                Rrotate(now);
                now->color=color;
                now->left->color=now->right->color=black;
                return false;
            }
            else if(now->color==red)
            {
                now->color=black;
                now->left->color=red;
                return false;
            }
            else if(now->color==black)
            {
                double_black=now;
                now->left->color=red;
                return true;
            }

        }
        return false;
    }   

    bool SuccessOr(RBnode*&now,int &key) 
    {
        bool NeedMaintain=false;

        if(now->right==root)
        {
            RBnode*temp=now;
            key=now->key;
            now=now->left;
            
            if(temp->color==red)NeedMaintain=false;
            else if(now->color==red)
            {
                 now->color=black;
                 NeedMaintain=false;
            }
            else
            {
                double_black=now;
                NeedMaintain=true;
            }

            delete temp;
            return NeedMaintain;
        }
        
        NeedMaintain=SuccessOr(now->right,key);

        if(NeedMaintain)return erase_maintain(now);
        update(now);
        return NeedMaintain;
    }

    bool erase(RBnode*&now,int &key)
    {
        bool NeedMaintain=false;

        if(now==root)return reslut=false;
        else if(now->key<key)NeedMaintain=erase(now->right,key);
        else if(now->key>key)NeedMaintain=erase(now->left,key);
        else
        {
            reslut=true;

            if(now->left==root)
            {
                RBnode*temp=now;
                now=now->right;

                if(temp->color==red)NeedMaintain=false;
                else if(now->color==red)
                {
                    now->color=black;
                    NeedMaintain=false;
                }
                else
                {
                    double_black=now;
                    NeedMaintain=true;
                }

                delete temp;
                return NeedMaintain;
            }
            else if(now->right==root)
            {
                RBnode*temp=now;
                now=now->left;
                
                if(temp->color==red)NeedMaintain=false;
                else if(now->color==red)
                {
                    now->color=black;
                    NeedMaintain=false;
                }
                else
                {
                    double_black=now;
                    NeedMaintain=true;
                }

                delete temp;
                return NeedMaintain;
            }
            
            NeedMaintain=SuccessOr(now->left,now->key);
        }

        if(NeedMaintain)
            return erase_maintain(now);
        update(now);
        return NeedMaintain;
    }


    bool insert_maintain(RBnode *&now) // 返回值为NeedMaintain
    {
        update(now);
        if (!hasRedChild(now))
            return false;
        else if (now->left->color == red && now->right->color == red)
        {
            if (!hasRedChild(now->left) && !hasRedChild(now->right))
                return false;
            now->left->color = now->right->color = black;
            now->color = red;
            return true;
        }
        else if (now->left->color == red)
        {
            if (!hasRedChild(now->left))
                return true;

            if (now->left->right->color == red)
                Lrotate(now->left);
            Rrotate(now);

            now->color = black;
            now->right->color = red;
            return false;
        }
        else if (now->right->color == red)
        {
            if (!hasRedChild(now->right))
                return true;

            if (now->right->left->color == red)
                Rrotate(now->right);
            Lrotate(now);
            now->color = black;
            now->left->color = red;
            return false;
        }
        return true;
    }

    bool insert(RBnode *&now, int &key)
    {
        bool NeedMaintain = false;

        if (now == root)
        {
            now = new RBnode(key); // 默认为红色
            now->left = now->right = root;
            ++Size;
            reslut = true;
            return true;
        }
        else if (key > now->key)
            NeedMaintain = insert(now->right, key);
        else
            NeedMaintain = insert(now->left, key);

        if (NeedMaintain)
            return insert_maintain(now);

        update(now);
        return NeedMaintain;
    }

    RBnode *search(RBnode *&now, int &key)
    {
        if (now == root)
            return nullptr;
        else if (now->key > key)
            return search(now->left, key);
        else if (now->key < key)
            return search(now->right, key);
        else
            return now;
    }

    void Lrotate(RBnode *&T)
    {
        RBnode *right = T->right;
        T->right = right->left;
        right->left = T;
        T = right;
        update(T->left), update(T);
    }

    void Rrotate(RBnode *&T)
    {
        RBnode *left = T->left;
        T->left = left->right;
        left->right = T;
        T = left;
        update(T->right), update(T);
    }

    bool hasRedChild(RBnode *&T)
    {
        if (T == root)
            return false;
        return T->left->color == red || T->right->color == red;
    }

    void update(RBnode *now)
    {
        if (now == root)
            return;
        now->Size = now->left->Size + now->right->Size + 1;
    }
};

int main()
{

     ios::sync_with_stdio(false);
     cin.tie(0),cout.tie(0);

    RBTree it;

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
            cout<<it.search(x)->key<<'\n';
        }
        
    } 

    cout << endl;
    system("pause");
    return 0;
}