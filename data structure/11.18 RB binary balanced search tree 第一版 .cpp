#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

// 红黑树定义：
// 1.每个节点非黑即红
// 2.根为黑
// 3.叶子节点(nullptr)为黑
// 4.红色节点的子节点为黑
// 5.从根触发的到所有叶子节点的路径上，黑色节点个数相同

// 方法论：
// 1.插入调整看祖父(从节点角度考虑，A插入至B孩子，A的祖父即B的父亲，也就是说对变动节点B来说，还是要看父亲节点)
// 2.删除节点看父亲
// 3.插入，删除的情况处理共五种

// PS：对于一个节点，如果其为黑色，其两个子节点均为红色，
// 这时，把两个子节点染成黑色，这个节点染成红色，之后这个子树仍然是红黑树，但是其上面的树可能需要调整，比如父节点如果是红色

// 对当前节点只涂黑不涂红，

const short black = 1;
const short red = 0;
const short double_red = 3;
const short double_black = 2;

struct RBnode
{
    RBnode *left, *right;
    int key, value;
    short color;
    RBnode(int x) : key(x), value(1), color(red) {}
};

class RBTree
{
private:
    unsigned int Size;
    RBnode *root;

public:
    RBTree()
    {
        root = new RBnode(0);
        // 设置一个头结点，同时把所有空指针全部指向头结点。
        // 头结点设置为黑，这与红黑树定义中的叶子结点为黑色是一致的。
        root->color = black;
        root->left = root->right = root; // 为了全部都指向头结点
        Size = 0;
    }

    bool insert(int x)
    {
        return insert(root->left, x);
    }

    RBnode *search(int x)
    {
        return search(root->left, x);
    }

    bool erase(int x)
    {
        bool flag=erase(root->left,x);
        root->left->color=black;
        return flag;
    }

    bool isRBTree(){//判断是否是RB树，判断方法：每个子树中 左子树黑色路径最小值等于左子树黑色路径最大值
        bool flag=true;
        int maxn=-1e9,minn=1e9;
        isRBTree(root->left,maxn,minn,flag);
        return flag;
    }
private:
    void erase_maintain(RBnode*&now)
    {
        if(now->left->color!=double_black&&now->right->color!=double_black)return;

        if(now->left->color==double_black)
        {
            if(now->left->color==red)
            {
                now->color=red;
                now->left->color=black;
                Rrotate(now);
                erase_maintain(now->right);
                return;
            }

            if(!hasRedChild(now->left))
            {
                now->color+=1;
                now->left->color-=1;
                now->right->color-=1;
                return;
            }

            if(now->left->left->color!=red)
            {
                now->left->right->color=black;
                now->left->color=red;
                Lrotate(now->left);
            }

            now->left->color=now->color;
            now->right->color-=1;
            Rrotate(now);
            now->left->color=now->right->color=black;
        }
        else
        {
            if(now->right->color==red)
            {
                now->color=red;
                now->right->color=black;
                Lrotate(now);
                erase_maintain(now->left);
                return;
            }

            if(!hasRedChild(now->right))
            {
                now->color+=1;
                now->left->color-=1;
                now->right->color-=1;
                return;
            }

            if(now->right->right->color!=red)
            {
                now->right->left->color=black;
                now->right->color=red;
                Rrotate(now->right);
            }

            now->right->color=now->color;
            now->left->color-=1;
            Lrotate(now);
            now->left->color=now->right->color=black;
        }

        return;        
    }

    void SuccessOr(RBnode*&now,int &key)//因为这个是赋值的方法，所以now必须引用
    {
        if(now->right==root)
        {
            RBnode*temp=now;
            key=move(now->key);
            now=now->left;//这句话很关键，让father不用当做参数传递的同时解决了特殊情况
            now->color+=temp->color;
            delete temp;
        }
        else
        {
            SuccessOr(now->right,key);       
        }

        erase_maintain(now);
        return;
    }

    bool erase(RBnode*&now,int &key)
    {
        bool flag=false;

        if(now==root)return false;
        else if(now->key>key)flag=erase(now->left,key);
        else if(now->key<key)flag=erase(now->right,key);
        else
        {
            if(--now->value>0)return false;

            flag=true;

            if(now->left==root||now->right==root)
            {
                RBnode*temp=(now->left==root)?now->right:now->left;
                temp->color+=now->color;
                delete now;
                now=temp;
            }
            else
            {
                SuccessOr(now->left,now->key);
            }
        }

        if(flag)
            erase_maintain(now);
        return flag;
    }

    int isRBTree(RBnode*now,int &maxn,int&minn,bool &flag){
        if(now==root)return 0;
        int l=isRBTree(now->left,maxn,minn,flag);
        int r=isRBTree(now->right,maxn,minn,flag);
        maxn=max({maxn,l,r});
        minn=min({minn,l,r});
        if(maxn!=minn)flag=0;
        return maxn;
    }
    
    void insert_maintain(RBnode *&now)
    {
        if (!hasRedChild(now))
            return;
        else if (now->left->color == red && now->right->color == red) // 如果左右均为红
        {
            if (!hasRedChild(now->left) && !hasRedChild(now->right))
                return;
            now->left->color = now->right->color = black;
            now->color = (now == root->left) ? black : red;
            // 这样可以保证根节点不会出现红色，因为在根节点处，即使让两个子节点直接为黑也不会破坏性质
        }
        else if (now->left->color == red)
        {
            if (!hasRedChild(now->left))
                return;
            if (now->left->right->color == red)
                Lrotate(now->left);
            Rrotate(now);

            // 这样处理才不会是根节点变红
            now->color = black;
            now->right->color = red;
        }
        else if (now->right->color == red)
        {
            if (!hasRedChild(now->right))
                return;
            if (now->right->left->color == red)
                Rrotate(now->right);
            Lrotate(now);
            now->color = black;
            now->left->color = red;
        }

        // 这种处理方案会让根节点变红，很奇怪，这是不合理的
        //  now->color=red;
        //  now->left->color=now->right->color=black;
        return;
    }

    bool insert(RBnode *&now, int &key)
    {
        bool flag = false;

        if (now == root)
        {
            now = new RBnode(key);//默认为红色
            now->left = now->right = root;
            if(now==root->left)now->color=black;//如果是根，就涂成黑色
            ++Size;
            return true;
        }
        else if (now->key > key)
            flag = insert(now->left, key);
        else if (now->key < key)
            flag = insert(now->right, key);
        else
        {
            ++now->value;
            return false;
        }

        if (flag)
            insert_maintain(now);
        return flag;
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
    }

    void Rrotate(RBnode *&T)
    {
        RBnode *left = T->left;
        T->left = left->right;
        left->right = T;
        T = left;
    }

    bool hasRedChild(RBnode *&T)
    {
        if (T == root)
            return false;
        return T->left->color == red || T->right->color == red;
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

     RBTree it;
     int n;
     cin >> n;
    
    int a[n + 1];

    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        it.insert(a[i]);
    }

    sort(a + 1, a + 1 + n);

    for (int i = 1; i <= n; ++i)
    {
        RBnode *res = it.search(a[i]);

        cout << res->key << ' ';
        
        it.erase(a[i]);

    }

    cout << endl;
    system("pause");
    return 0;
}
