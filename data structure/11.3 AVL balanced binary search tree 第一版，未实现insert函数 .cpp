#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

typedef struct AVLNode
{
    AVLNode *l = nullptr, *r = nullptr, *p = nullptr;
    int data, bf = 0,value=0;
} *AVLTree;

class myAVLTree
{
private:
    AVLTree tree;
    int Size;

    void Lrotate(AVLTree &T)
    {
        AVLTree R = T->r;

        T->r = R->l;
        R->l = T;

        if (T->p->l == T)
            T->p->l = R;
        else
            T->p->r = R;

        R->p = T->p;
        T->p = R;

        if (T->r != nullptr)
            T->r->p = T;

        T->bf = R->bf = 0;
    }

    void Rrotate(AVLTree &T)
    {
        AVLTree L = T->l;

        T->l = L->r;
        L->r = T;

        if (T->p->l == T)
            T->p->l = L;
        else
            T->p->r = L;

        L->p = T->p;
        T->p = L;

        if (T->l != nullptr)
            T->l->p = T;

        T->bf = L->bf = 0;
    }

    void LLR(AVLTree &T)
    {
        Rrotate(T);
    }

    void LRLR(AVLTree &T)
    {
        AVLTree L = T->l;
        int bf = L->r->bf;

        Lrotate(T->l);
        Rrotate(T);

        if (bf == 1)
            T->bf = -1;
        else if (bf == -1)
            L->bf = 1;
    }

    void RRL(AVLTree &T)
    {
        Lrotate(T);
    }

    void RLRL(AVLTree &T)
    {
        AVLTree R = T->r;
        int bf = R->l->bf;

        Rrotate(T->r);
        Lrotate(T);

        if (bf == 1)
            R->bf = -1;
        else if (bf == -1)
            T->bf = 1;
    }

    void rebalance(AVLTree p, int k)
    {
        AVLTree f = p->p;

        while (f != tree)
        {
            if (f->l == p)
                f->bf += k;
            else
                f->bf -= k;

            if (f->bf == 0)
                break;
            else if (f->bf == 1 || f->bf == -1)
                p = f, f = f->p;
            else
            {
                if (f->bf == 2)
                {
                    if (p->bf == 1)
                        LLR(f);
                    else
                        LRLR(f);
                }
                else
                {
                    if (p->bf == -1)
                        RRL(f);
                    else
                        RLRL(f);
                }

                break;
            }
        }
    }

    int GetDepth(AVLTree root)
    {
        if (root == nullptr)
            return 0;
        return max(GetDepth(root->l), GetDepth(root->r)) + 1;
    }

    bool check(AVLTree root)
    {
        if (root == nullptr)
            return true;
        ;
        int l = GetDepth(root->l);
        int r = GetDepth(root->r);

        if (abs(l - r) > 1 || l - r != root->bf)
            return false;

        return check(root->l) && check(root->r);
    }

public:
    myAVLTree()
    {
        tree = new AVLNode;
        Size = 0;
    }

    bool insert(int x)
    {
        if (tree->l == nullptr)
        {
            tree->l = new AVLNode;
            tree->l->p = tree;
            tree->l->data = x;
            tree->l->value=1;
            ++Size;
            return true;
        }

        AVLNode *p = tree->l, *f = tree;

        while (p != nullptr)
        {
            if (p->data == x)
            {
                p->value++;
                return false;
            }

            f = p;

            if (x > p->data)
                p = p->r;
            else
                p = p->l;
        }

        p=new AVLNode;
        p->p=f;
        p->data=x;
        p->value=1;
        
        if(x>f->data)f->r=p;
        else f->l=p;

        while(p!=tree)
        {
            if(f->l==p)++f->bf;
            else --f->bf;

            if(f->bf==0)break;
            else if(f->bf==-1||f->bf==1)
                p=f,f=f->p;
            else
            {    
                if(f->bf==2)
                {
                    if(p->bf==1)LLR(f);
                    else LRLR(f);
                }
                else
                {
                    if(p->bf==-1)RRL(f);
                    else RLRL(f);
                }

                break;
            }
        }

        return true;
    }

    AVLTree search(int x)
    {
        AVLTree p = tree->l;

        while (p != nullptr)
        {
            if (p->data == x)
                return p;

            if (x > p->data)
                p = p->r;
            else
                p = p->l;
        }

        return nullptr;
    }

    bool erase(int x)
    {
        AVLTree p = tree->l;

        while (p != nullptr)
        {
            if (p->data == x)
                break;

            if (x > p->data)
                p = p->r;
            else
                p = p->l;
        }

        if (p == nullptr)
            return false;

        if (p->l == nullptr)
        {
            AVLTree f = p->p;

            if (f->l == p)
            {
                --f->bf;
                f->l = p->r;
            }
            else
            {
                ++f->bf;
                f->r = p->r;
            }

            if (p->r != nullptr)
                p->r->p = f;

            delete p;

            rebalance(f, -1);
        }
        else
        {
            AVLTree l = p->l;

            while (l->r != nullptr)
                l = l->r;

            p->data = move(l->data);

            if (l->p == p)
            {
                --p->bf;
                p->l = nullptr;
                free(l);
                rebalance(p, -1);
            }
            else
            {
                ++l->p->bf;
                l->p->r = nullptr;
                free(l);
                rebalance(p, -1);
            }
        }

        return true;
    }

    int getdepth()
    {
        return GetDepth(tree->l);
    }

    bool isAVLTree()
    {
        return check(tree->l);
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    myAVLTree it;

    int n;

    cin >> n;

    while (n--)
    {
        int op, x;
        cin >> op;

        if (op == 1)
        {
            cin >> x;
            AVLTree p = it.search(x);

            if (p == nullptr)
                cout << "empty" << endl;
            else
                cout << p->data << endl;
        }
        else if (op == 2)
        {
            cin >> x;

            cout << it.insert(x) << endl;
        }
        else if (op == 3)
        {
            cin >> x;

            cout << it.erase(x) << endl;
        }
    }

    cout << endl;
    system("pause");
    return 0;
}
