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

// 插入站在祖父节点考虑，删除站在父节点考虑

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
    RBnode *root, *double_black; // double_black指向被删除节点的继任节点，用来判断是在父亲的左还是右
    bool reslut;                 // 作为返回值

public:
    bool IsBalance() // 判断平衡否
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
        double_black = nullptr; // 初始时指向空，这样不会出现冲突
        Size = 0;
    }

    bool insert(int x)
    {
        reslut = false;
        insert(root->left, x);
        root->left->color = black; // 根节点始终为黑色
        return reslut;
    }

    RBnode *search(int x)
    {
        return search(root->left, x);
    }

    bool erase(int x)
    {
        reslut = false;
        double_black = nullptr; // 先置空
        erase(root->left, x);
        root->left->color = black; // 根染黑
        return reslut;
    }

    int get_rank(int x)
    {
        RBnode *now = root->left;
        int rank = 1;

        while (now != root && now != nullptr)
        {
            if (x <= now->key)
                now = now->left;
            else
            {
                rank += now->left->Size + 1;
                now = now->right;
            }
        }

        return rank;
    }
    int get_val(int rank)
    {
        RBnode *now = root->left;

        while (now != root && now != nullptr)
        {
            if (now->left->Size + 1 == rank)
                break;
            else if (now->left->Size >= rank)
                now = now->left;
            else
            {
                rank -= now->left->Size + 1;
                now = now->right;
            }
        }

        return now->key;
    }
    int get_pre(int x)
    {
        RBnode *p = root->left;
        int pre;

        while (p != root && p != nullptr)
        {
            if (p->key < x)
                pre = p->key, p = p->right;
            else
                p = p->left;
        }

        return pre;
    }

    int get_next(int x)
    {
        RBnode *p = root->left;
        int next;

        while (p != root && p != nullptr)
        {
            if (p->key > x)
                next = p->key, p = p->left;
            else
                p = p->right;
        }

        return next;
    }

private:
    bool erase_maintain(RBnode *&now) // 返回值为是否需要继续调整
    {
        update(now);
        if (double_black == nullptr)
            return false;                   // 处理特殊情况
        else if (now->left == double_black) // 在左边的情况，下面的在右边情况一致
        {
            double_black = nullptr; // 直接至为空，

            if (now->right->color == red)
            // 处理最难的情况，实际上，兄弟为红给了很多信息，
            // 1.父亲为黑 2.因为被删除节点为黑色叶子，所以兄弟必有两个黑色叶子节点 3.兄弟的两个孩子可能还有红色叶子结点
            {
                now->right->color = black; // 交换颜色
                now->color = red;
                Lrotate(now);                     // 左旋当前节点
                double_black = now->left->left;   // 这个时候把被删除节点当做左孙子，实际上左孙子必为空
                return erase_maintain(now->left); // 然后当做左孩子被删
            }

            if (hasRedChild(now->right)) // 有红孩子，可以借。兄弟为红可能会转移到这里。
            {
                bool color = now->color;               // 父亲颜色
                if (now->right->right->color == black) // 说明是RL型红孩子，先右旋
                    Rrotate(now->right);
                Lrotate(now);                                 // 左旋
                now->color = color;                           // 当前继任原父亲节点颜色，
                now->left->color = now->right->color = black; // 孩子染黑
                return false;                                 // 不需要调整
            }
            else if (now->color == red) // 父亲为红，双子为黑，并且左为叶子，简单的互换颜色即可。兄弟为红可能会转移到这里
            {
                now->color = black;
                now->right->color = red;
                return false;
            }
            else if (now->color == black)
            // 父亲为黑，兄弟为黑并且没有红孩子，这个时候把兄弟染红之后相当于当前子树少了一个黑色节点，交给祖父处理，
            {
                now->right->color = red;
                double_black = now; // double_black设置为当前
                return true;
            }
        }
        else if (now->right == double_black)
        {
            double_black = nullptr;

            if (now->left->color == red)
            {
                now->left->color = black;
                now->color = red;
                Rrotate(now);
                double_black = now->right->right;
                return erase_maintain(now->right);
            }

            if (hasRedChild(now->left))
            {
                bool color = now->color;
                if (now->left->left->color == black)
                    Lrotate(now->left);
                Rrotate(now);
                now->color = color;
                now->left->color = now->right->color = black;
                return false;
            }
            else if (now->color == red)
            {
                now->color = black;
                now->left->color = red;
                return false;
            }
            else if (now->color == black)
            {
                double_black = now;
                now->left->color = red;
                return true;
            }
        }
        return false;
    }

    bool SuccessOr(RBnode *&now, int &key) // 寻找前驱，并且替代key值
    {
        bool NeedMaintain = false; // 还是判断是否需要删除调整

        if (now->right == root) // 找到了前驱
        {
            RBnode *temp = now;
            key = now->key;  // 值替代
            now = now->left; // 注意写法，引用型参数，这里会直接修改父亲的左孩子或者右孩子的指针

            if (temp->color == red)
                NeedMaintain = false;   // 红色，不需要
            else if (now->color == red) // 继任者为红色，不需要
            {
                now->color = black;
                NeedMaintain = false;
            }
            else // 不然，doubleblack指向
            {
                double_black = now;
                NeedMaintain = true;
            }

            delete temp;
            return NeedMaintain;
        }

        NeedMaintain = SuccessOr(now->right, key);

        if (NeedMaintain)
            return erase_maintain(now);
        update(now);
        return NeedMaintain;
    }

    bool erase(RBnode *&now, int &key)
    {
        bool NeedMaintain = false; // 表示是否需要删除调整，降低一些常数

        if (now == root)
            return reslut = false;
        else if (now->key < key)
            NeedMaintain = erase(now->right, key);
        else if (now->key > key)
            NeedMaintain = erase(now->left, key);
        else
        {
            reslut = true;

            if (now->left == root) // 先判断度是否已经小于等于1
            {
                RBnode *temp = now;
                now = now->right;

                if (temp->color == red)
                    NeedMaintain = false;   // 红色，不需要调整
                else if (now->color == red) // 有红孩子，不需要调整
                {
                    now->color = black; // 染红
                    NeedMaintain = false;
                }
                else // 黑色叶子节点
                {
                    double_black = now; // double_black指向继任者，需要调整
                    NeedMaintain = true;
                }

                delete temp; // 删除
                return NeedMaintain;
            }
            else if (now->right == root)
            {
                RBnode *temp = now;
                now = now->left;

                if (temp->color == red)
                    NeedMaintain = false;
                else if (now->color == red)
                {
                    now->color = black;
                    NeedMaintain = false;
                }
                else
                {
                    double_black = now;
                    NeedMaintain = true;
                }

                delete temp;
                return NeedMaintain;
            }

            // 度为2的节点，先去寻找前驱，并且注意这个地方不能return
            NeedMaintain = SuccessOr(now->left, now->key);
        }

        if (NeedMaintain)
            return erase_maintain(now);
        update(now);
        return NeedMaintain;
    }

    bool insert_maintain(RBnode *&now) // 解决双红现象，返回值为NeedMaintain
    {
        // 插入策略，因为站在祖父节点，所以理应在父亲的时候会出现直接返回true的情况

        update(now);
        if (!hasRedChild(now)) // 祖父节点没有红孩子，不再需要调整，直接false
            return false;
        else if (now->left->color == red && now->right->color == red) // 左右均为红
        {
            if (!hasRedChild(now->left) && !hasRedChild(now->right)) // 没有红色孙子，不需要调整
                return false;
            now->left->color = now->right->color = black; // 交换颜色
            now->color = red;                             // 父亲染成红色（根节点这个时候可能为红，之后会在inset进行处理）
            return true;
        }
        else if (now->left->color == red) // 左孩子为红
        {
            if (!hasRedChild(now->left)) // 但是没有红孙子，说明这个时候可能是站在父亲节点，所以return true再次进行调整
                return true;

            if (now->left->left->color == black) // 说明LR型红孙子，需要左旋
                Lrotate(now->left);
            Rrotate(now);

            now->color = black; // 父亲，孩子交换染色
            now->right->color = red;
            return false;
        }
        else if (now->right->color == red)
        {
            if (!hasRedChild(now->right))
                return true;

            if (now->right->right->color == black) // 说明是RL型红孙子，需要右旋
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
        bool NeedMaintain = false; // 定义变量NeedMaintain表示该节点的父节点是否需要调整，用于降低常数

        if (now == root)
        {
            now = new RBnode(key); // 默认为红色
            now->left = now->right = root;
            ++Size;
            reslut = true;
            return true; // 插入，
        }
        else if (key > now->key)
            NeedMaintain = insert(now->right, key);
        else // 这里允许了重复插入
            NeedMaintain = insert(now->left, key);

        if (NeedMaintain) // 需要调整，调用insertmaintain
            return insert_maintain(now);

        update(now); // 不需要调整，更新一下节点的Size值
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
        update(T->left), update(T); // 别忘了更新Size
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
        if (T == root) // 空节点，返回false
            return false;
        return T->left->color == red || T->right->color == red;
    }

    void update(RBnode *now)
    {
        if (now == root) // 头结点，不管
            return;
        now->Size = now->left->Size + now->right->Size + 1;
    }
};

int main()
{

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    RBTree it;

    int n;
    cin >> n;

    while (n--)
    {
        int op, x;
        cin >> op >> x;

        if (op == 1)
        {
            it.insert(x);
        }
        else if (op == 2)
        {
            it.erase(x);
        }
        else if (op == 3)
        {
            cout << it.get_rank(x) << '\n';
        }
        else if (op == 4)
        {
            cout << it.get_val(x) << '\n';
        }
        else if (op == 5)
        {
            cout << it.get_pre(x) << '\n';
        }
        else if (op == 6)
        {
            cout << it.get_next(x) << '\n';
        }
        else if (op == 7)
        {
            cout << it.search(x)->key << '\n';
        }
    }

    cout << endl;
    system("pause");
    return 0;
}