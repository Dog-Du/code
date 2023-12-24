#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <fstream>

#define ll long long

using namespace std;

// B-树给我的启示：
// 1.不要在脑子模糊的情况下写算法
// 2.函数的接口要尽可能简单，越方便调用越好
// 3.打持久战要有耐心
// 4.调试函数的存在可能比一个有用的函数更重要
// 5.不要超过两个小时持续思考
// 6.别人的代码可以看，可以借鉴，但是不能全信，
//我看的别人的代码想法很美妙，但是不能细想，一细想发现漏洞百出
// 7.有想法了就去实现
// 8.对拍或者利用oj是个不错的想法
// 9.与AVL树相同，对自己的数据结构制定一个规则，然后通过优雅的方式实现，代码的效率就会极大地提升


//吐槽：B-树真的不仅仅是把分块思想用到了排序树吗？
#define m 5

struct node
{
    int key, value;
    bool operator<(const node &it) const
    {
        return key < it.key;
    }
    bool operator>(const node &it) const
    {
        return key > it.key;
    }
    bool operator==(const node &it) const
    {
        return key == it.key;
    }
};

struct BTnode
{
    BTnode *parent = nullptr;
    int keynum = 0;
    BTnode *child[m + 1] = {0};
    node key[m + 1];
    int Size[m + 1] = {0};
};

struct Result
{
    BTnode *ptr;
    bool tag;
    int i;
};

class B_Tree
{
private:
    int Size;
    BTnode *root;
    const int key_min = (m - 1) / 2;
    const int mid = (m + 1) / 2;
    const int key_max = m - 1;

public:
    B_Tree()
    {
        Size = 0;
        root = nullptr;
    }

    bool insert(int x)
    {
        Result res = search(x);

        if (res.tag) // 找到了，就个数+1
        {
            ++res.ptr->key[res.i].value;
            return false;
        }
        else
        {
            insert(root, {x, 1}, res);
            ++Size;
            return true;
        }
    }

    Result search(int x) // 找位置，函数很简单，没啥好说的
    {
        BTnode *p = root, *q = nullptr;
        int i;
        bool flag = 0;
        node key = {x, 1};

        while (p != nullptr && !flag)
        {
            i = findpos(p, key);

            if (i <= p->keynum && p->key[i] == key)
                flag = 1;
            else
            {
                q = p;
                p = p->child[i - 1];
            }
        }

        if (flag)
            return {p, flag, i};
        else
            return {q, flag, i};
    }

    bool erase(int x)
    {
        Result res = search(x);

        if (res.tag)
        {
            if (--res.ptr->key[res.i].value == 0)
                erase(root, {x, 1}, res);
            return true;
        }
        else
            return false;
    }

    /* 计算出整棵树上记录条数的总和 */
    int CountKeyNum(BTnode *tree)
    {
        // 空树则为 0
        if (tree == NULL)
            return 0;

        // 计算所有子树记录条数总和
        int childTotal = 0;
        for (int i = 0; i <= tree->keynum; i++)
        {
            childTotal += CountKeyNum(tree->child[i]);
        }

        // 子树加上自身的记录条数，即为总记录条数
        return tree->keynum + childTotal;
    }

    /* 打印 B 树 */
    void TraverseBTree(BTnode *tree = nullptr)
    { // 看的别人代码直接复制粘贴的调试函数

        // 动态创建一个数组，用于存放当前结点是否为最后结点的标识
        tree = this->root;
        int nowNum = 0;
        int *isLast = (int *)malloc(sizeof(int) * (CountKeyNum(tree) + 10));

        // 打印树形
        printf("\n");
        PrintBTree(tree, isLast, nowNum);
    }

    /* 递归打印树形 */
    void PrintBTree(BTnode *tree, int isLast[], int nowNum)
    {
        // 空树直接跳过
        if (tree == nullptr)
            return;

        // 打印新节点先打印一下平台
        printf("-|\n");
        for (int i = 0; i <= tree->keynum; i++)
        {
            if (tree->child[i] != NULL)
            {
                printBranch(isLast, nowNum);
                printf("|----");
                isLast[nowNum++] = (i == tree->keynum);
                PrintBTree(tree->child[i], isLast, nowNum);
                nowNum--;
            }
            if (i != tree->keynum)
            {
                printBranch(isLast, nowNum);
                printf("|- %d\n", tree->key[i + 1].key);
            }
        }
    }

    /* 打印树枝 */
    void printBranch(int isLast[], int nowNum)
    {
        for (int i = 0; i < nowNum; i++)
        {
            if (isLast[i])
                printf(" ");
            else
                printf("|");
            printf("      ");
        }
    }

private:
    
    void Merge(BTnode *&left, BTnode *&right) // 把右边归并到左边，并删除右边的节点
    {
        for (int i = left->keynum + 1, j = 1; j <= right->keynum; ++j, ++i)
        {
            left->key[i] = right->key[j];
            left->child[i] = right->child[j];

            if (left->child[i] != nullptr) // 把孩子更改父亲
                left->child[i]->parent = left;
            ++left->keynum;
        }

        delete right;
        right = left;
    }

    void Adjust(BTnode *&p) // 调整树型
    {
        BTnode *parent = p->parent, *brother;
        int i;

        while (p->keynum < key_min && parent != nullptr) // 如果节点个数比较少，同时不为根节点
        {
            i = findpos(parent, p->key[1]); // 父亲的编号 当前在 child[i-1] 中

            if (i > 1 && (brother = parent->child[i - 2]) != nullptr) // 左兄弟不为空， 当前在 child[i-1] 那么 child[i-2]就是左兄弟了
            {
                if (brother->keynum > key_min) // 左兄弟富裕
                {
                    InsertBTnode(p, parent->key[i - 1], brother->child[brother->keynum]); // 把父亲的节点要下来，注意把左兄弟最右端的指针也拿下来
                    swap(p->child[0], p->child[1]);
                    brother->child[brother->keynum] = nullptr;
                    // 这里不需要像有兄弟一样把 child[brother->keynum] 置空，因为减1了，画个图就明白了
                    parent->key[i - 1] = brother->key[brother->keynum]; // 然后父亲替换成左兄弟的最大值
                    Remove(brother, brother->key[brother->keynum]);     // 左兄弟删除这个节点，
                    break;                                              // 调整完成，break
                }
                else // 左兄弟穷
                {
                    InsertBTnode(brother, parent->key[i - 1], p->child[0]); // 把父亲要下来，这个时候父亲那个节点要被删除，把兄弟最右端指针拿下来
                    p->child[0] = nullptr;
                    Remove(parent, parent->key[i - 1]); // 删除父亲
                    Merge(brother, p);                  // 合并兄弟

                    p = p->parent; // 父亲可能节点变少，继续循环
                    parent = p->parent;
                }
            }
            else if (i <= parent->keynum && (brother = parent->child[i]) != nullptr) // 有右兄弟
            {
                if (brother->keynum > key_min) // 右兄弟富裕
                {
                    InsertBTnode(p, parent->key[i], brother->child[0]);
                    brother->child[0] = brother->child[1]; // 这一句别忘了多加，因为右兄弟最左端节点被我拿走了，所以附带的他也为空
                    parent->key[i] = brother->key[1];
                    Remove(brother, brother->key[1]);
                    break;
                }
                else // 右兄弟穷
                {
                    InsertBTnode(p, parent->key[i], brother->child[0]);
                    Remove(parent, parent->key[i]);
                    Merge(p, brother); // 注意这个时候p在左边，brother在右边

                    p = p->parent;
                    parent = p->parent;
                }
            }
            else // 如果没有直接相邻的左右兄弟，啥也不管了，直接把父亲拽下来，然后迭代父亲
            {
                InsertBTnode(p, parent->key[i], nullptr); // 没有左右兄弟，所以为nullptr
                Remove(parent, parent->key[i]);           // 这样是合理的，因为 parent->child[i] 为空

                p = p->parent;
                parent = p->parent;
            }

            // TraverseBTree();
        }

        // 如果变成了根节点，根据定义，根至少有两个孩子，但可以keynum可以少于key_min

        if (parent == nullptr && p->keynum == 0) // 如果根节点keynum为零了，找一个孩子替代它
        {
            root = (root->child[0] == nullptr) ? root->child[1] : root->child[0];
            root->parent = nullptr;
            delete p;
        }
    }

    void Remove(BTnode *&p, node &x) // 删除函数，给出节点指针和数值，别管这个数值在哪里，不然很麻烦，交给这个函数处理
    {
        int i = findpos(p, x);
        for (int j = i; j <= p->keynum; ++j)
            p->key[j] = p->key[j + 1],
            p->child[j] = p->child[j + 1];
        --p->keynum;
    }

    void SuccessOr(Result &res) // 找到后继，替代，并且删除本身
    {
        // 注意是引用
        int &i = res.i;
        BTnode *&p = res.ptr;

        if (p->child[i - 1] != nullptr) // 有直接左孩子
        {
            BTnode *pre = p->child[i - 1];

            while (pre->child[pre->keynum] != nullptr)
                pre = pre->child[pre->keynum];

            p->key[i] = pre->key[p->keynum];
            p = pre;
            i = p->keynum;
            Remove(p, p->key[i]);
        }
        else if (p->child[i] != nullptr) // 有直接右孩子
        {
            BTnode *next = p->child[i];

            while (p->child[0] != nullptr)
                p = p->child[0];

            p->key[i] = next->key[1];
            p = next;
            i = 1;
            Remove(p, p->key[i]);
        }
        else if (i > 1) // 有直接左兄弟
        {
            p->child[i - 1] = p->child[i];
            Remove(p, p->key[i]);
        }
        else if (i < p->keynum) // 有直接右兄弟
        {
            Remove(p, p->key[i]);
        }
        // else
        // //在本层及以下没有前驱后继，也就是说这个节点只剩下一个了，
        // //删除这个节点之后应该直接释放这个节点，但实际上这个情况不可能出现（m大于4时）所以不管它了
        // {
        //     Remove(p, p->key[i]);
        // }
    }

    void erase(BTnode *&root, node key, Result &res)
    {
        SuccessOr(res);

        // BTnode *p = res.ptr;

        Adjust(res.ptr);

        // if (p->parent != nullptr && p->keynum < key_min)
        // {
        //     Adjust(p); // 调整
        // }
        // else if (p->parent == nullptr && p->keynum == 0)//如果出现了这种情况，不应该这样处理，应该想Adjust那样处理
        // {
        //     delete root;
        //     root = nullptr;
        // }
    }

    void newroot(BTnode *&root, BTnode *&child1, BTnode *&child2, node &key) // 如果根节点出现了分裂或者初始为空,需要新建一个节点
    {
        root = new BTnode;
        root->keynum = 1;
        root->key[1] = key;
        root->child[0] = child1;
        root->child[1] = child2;
        root->parent = nullptr;

        if (child1 != nullptr)
            child1->parent = root;
        if (child2 != nullptr)
            child2->parent = root;
        return;
    }

    void split(BTnode *&p, BTnode *&ap) // p分裂，并分给ap
    {
        ap = new BTnode;
        ap->child[0] = p->child[mid]; // 别忘了

        for (int i = mid + 1, j = 1; i <= p->keynum; ++i, ++j)
            ap->key[j] = p->key[i],
            ap->child[j] = p->child[i];

        ap->parent = p->parent;
        ap->keynum = p->keynum - mid;
        p->keynum = mid - 1;

        // 双亲和孩子的双向绑定
        for (int i = 0; i <= ap->keynum; ++i)
            if (ap->child[i] != nullptr)
                ap->child[i]->parent = ap;

        return;
    }

    void InsertBTnode(BTnode *&p, node &key, BTnode *ap) // 给出节点，值和指针，不要给出i！！！不然会变得不幸！
    {
        int i = findpos(p, key); // i在这里现场获得！！！

        for (int j = p->keynum; j >= i; --j)
            p->key[j + 1] = p->key[j],
                       p->child[j + 1] = p->child[j];

        p->child[i] = ap;
        p->key[i] = key;
        p->keynum++;
        if (ap != nullptr)
            ap->parent = p;
        return;
    }

    void insert(BTnode *&root, node key, Result &res) // 插入
    {
        BTnode *ap = nullptr, *p = res.ptr;
        bool finished = false;
        // int i = res.i;//这个i其实屁用没有，因为我坚持i一定要现场获得，不然会变得不幸！

        while (p != nullptr && !finished)
        {
            InsertBTnode(p, key, ap);

            if (p->keynum <= key_max)
                finished = 1;
            else
            {
                split(p, ap);
                key = p->key[mid];

                if (p->parent != nullptr)
                {
                    p = p->parent;
                    // i = findpos(p, key);//不要管i
                }
                else
                    break;
            }
        }

        if (!finished) // 如果p是根，说明要么根分裂了，要么树为空
            newroot(root, p, ap, key);
    }

    int findpos(BTnode *&q, node &x) // 作用：找这个节点中第一个大于等于x的下标，PS；永远不可能为0
    {
        return lower_bound(q->key + 1, q->key + 1 + q->keynum, x) - q->key;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    // fstream p;
    // p.open("E:\\DOWNLOAD\\P1177_4.in");

    B_Tree it;
    int n;
    cin >> n;

    while(n--)
    {
        int op,x;
        cin>>op>>x;

        if(op==1)
        {
            Result res=it.search(x);
            if(res.tag)cout<<res.ptr->key[res.i].key<<' '<<res.ptr->key[res.i].value<<endl;
            else cout<<"empty"<<endl;
        }
        else if(op==2)
        {
            cout<<it.insert(x)<<endl;
        }
        else if(op==3)
        {
            cout<<it.erase(x)<<endl;
        }

        it.TraverseBTree();
    }

    cout << endl;
    system("pause");
    return 0;
}
