#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1e5 + 10, N = 1e9;

// 如果使用Treap会超时，因为常数比较大，选用AVL树效率是最高的。
// 单次修改与单次修改时间复杂度 logn的平方

// 在值域上建立线段树，每个节点用平衡树维护下标即可。

struct AVLnode
{
    AVLnode *left, *right;
    int height, Size;
    int key;
};

class AVLTree
{
private:
    AVLnode *root;

public:
    AVLTree()
    {
        root = new AVLnode;
        root->left = root;
        root->right = root;
        root->height = 0;
        root->Size = 0;
    }

    inline void insert(int x)
    {
        ins(root->left, x);
    }
    inline void erase(int x)
    {
        del(root->left, x);
    }

    inline int get_rank(int x)
    {
        register AVLnode *now = root->left;
        register int rank = 1;

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

    inline int upper_bound(int x)
    {
        register AVLnode *now = root->left;
        register int rank = 1;

        while (now != root && now != nullptr)
        {
            if (x < now->key)
                now = now->left;
            else
            {
                rank += now->left->Size + 1;
                now = now->right;
            }
        }

        return rank;
    }

private:
    inline void del(AVLnode *&now, int &key)
    {
        if (now == root)
        {
            return;
        }
        else if (key > now->key)
            del(now->right, key);
        else if (key < now->key)
            del(now->left, key);
        else
        {
            register AVLnode *temp = now, *l = now->left, *r = now->right;

            if (l == root)
                now = r;
            else if (r == root)
                now = l;
            else
            {
                now = find(l, l); // 把这个节点剖下来

                if (now != l) // 如果不是直接为左边的
                    now->left = l;

                now->right = r;
            }
            delete temp;
        }

        check(now);
        return;
    }

    inline AVLnode *find(AVLnode *&now, AVLnode *fa)
    {
        register AVLnode *res;

        if (now->right == root)
        {
            res = now;
            fa->right = now->left;
        }
        else
        {
            res = find(now->right, now);
            check(now);
        }

        return res;
    }

    inline void ins(AVLnode *&now, int &key)
    {
        if (now == root)
        {
            newnode(now, key);
        }
        else if (key > now->key)
            ins(now->right, key);
        else
            ins(now->left, key);

        check(now);
    }

    inline void check(AVLnode *&T)
    {
        register int bf = factor(T);

        if (bf > 1)
        {
            register int lf = factor(T->left);
            if (lf >= 0)
                Rrotate(T);
            else
                Lrotate(T->left), Rrotate(T);
        }
        else if (bf < -1)
        {
            register int rf = factor(T->right);
            if (rf <= 0)
                Lrotate(T);
            else
                Rrotate(T->right), Lrotate(T);
        }
        else if (T != root)
            update(T);
    }

    inline int factor(AVLnode *&T)
    {
        if (T == root)
            return 0;
        return T->left->height - T->right->height;
    }

    inline void Rrotate(AVLnode *&T)
    {
        register AVLnode *L = T->left;
        T->left = L->right;
        L->right = T;
        T = L;
        update(T->right), update(T);
    }
    inline void Lrotate(AVLnode *&T)
    {
        register AVLnode *R = T->right;
        T->right = R->left;
        R->left = T;
        T = R;
        update(T->left), update(T);
    }
    inline void update(AVLnode *&T)
    {
        if (T == root)
            return;
        T->height = max(T->left->height, T->right->height) + 1;
        T->Size = T->left->Size + T->right->Size + 1;
    }
    inline void newnode(AVLnode *&T, int &key)
    {
        T = new AVLnode;
        T->left = T->right = root;
        T->height = 1;
        T->key = key;
    }
};

struct node
{
    AVLTree tree;
    node *left, *right;
    node(node *p) : left(p), right(p){};
} *root;

int a[maxn]; // a是原数组

int n, m, l, r, k, ans, x, y, L, R;

inline void insert(node *&now, int l, int r)
{
    if (now == nullptr)
        now = new node(nullptr);

    now->tree.insert(y);

    if (l == r)
        return;

    register int mid = l + r >> 1;
    if (mid >= x)
        insert(now->left, l, mid);
    else
        insert(now->right, mid + 1, r);
}

inline void erase()
{
    register node *p = root;
    register int mid, l = 0, r = N;
    // p->tree.erase(y);
    while (l != r)
    {
        mid = l + r >> 1;
        if (mid >= x)
        {
            p = p->left;
            r = mid;
        }
        else
        {
            p = p->right;
            l = mid + 1;
        }
        p->tree.erase(y);
    }
}

// 问左子树多少个数字的id在L，R之间，如果大于k，去左子树，如果小于k，去右子树，如果k等于0，那么得到答案
inline void query()
{
    register node *p = root;
    register int mid, cntl, cntr, l = 0, r = N;

    while (l != r)
    {
        cntl = 0, cntr = -1;

        if (p->left != nullptr)
            cntl = p->left->tree.get_rank(L),
            cntr = p->left->tree.upper_bound(R) - 1;

        mid = l + r >> 1;
        if (cntr - cntl + 1 >= k)
        {
            p = p->left;
            r = mid;
        }
        else
        {
            p = p->right;
            l = mid + 1;
            k -= (cntr - cntl + 1);
        }
    }
    ans = l;
}

int main()
{
    scanf("%d %d", &n, &m);

    root = new node(nullptr);

    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        x = a[i], y = i;
        insert(root, 0, N);
    }

    register char op[2];
    for (int i = 1; i <= m; ++i)
    {
        scanf("%s", &op);
        if (op[0] == 'Q')
        {
            scanf("%d %d %d", &L, &R, &k);
            query();
            printf("%d\n", ans);
        }
        else
        {
            scanf("%d %d", &l, &r);
            x = a[l], y = l;
            erase();
            a[l] = r;
            x = a[l], y = l;
            insert(root, 0, N);
        }
    }

    cout << endl;
    system("pause");
    return 0;
}
