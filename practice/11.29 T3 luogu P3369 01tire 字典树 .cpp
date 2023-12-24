#include <iostream>
#include <cmath>
using namespace std;

//01前缀树解决平衡树问题

const int maxn = 1e7 + 10, maxlog = ceil(log2(maxn));

//01Tire实现了类似平衡树的性质，左子树的都小于本身，右子树都大于本身。
//因为负数第一位为1，这和平衡树性质不符合，所以要把所有负数加一个极大值，转化成正数。

class Tire01
{
private:
    struct node//child[0]是0，child[1]是1。前缀
    {
        node *child[2];
        int size;
        node(node *p)
        {
            child[0] = child[1] = p;
            size = 0;
        }
    } *root;

    void clear(node*now)
    {
        if(now==root)return;
        clear(now->child[0]);
        clear(now->child[1]);
        delete now;
    }

public:

    void clear()
    {
        clear(root->child[0]);
        clear(root->child[1]);
    }

    ~Tire01()
    {
        clear();
        delete root;
    }

    Tire01()//设置头结点root，让所有空节点都指向root
    {
        root = new node(nullptr);
        root->child[0] = root->child[1] = root;
    }

    void insert(int x)
    {
        node *p = root;

        for (int i = maxlog, t; i >= 0; --i)//从最高位开始，这和数的比较从最高位开始是一致的
        {
            t = (x >> i) & 1;//这一位上的数字是0还是1

            if (p->child[t] == root)
                p->child[t] = new node(root);//如空，则新建

            p = p->child[t];
            ++p->size;
        }
    }

    void erase(int x)//删除则更简单，直接沿路删除即可，因为不需要释放空间，
    {
        node *p = root;

        for (int i = maxlog, t; i >= 0; --i)
        {
            t = (x >> i) & 1;
            p = p->child[t];
            --p->size;
        }
    }

    int get_val(int k)//根据排名获得值
    {
        node *p = root;
        int ans = 0;

        for (int i = maxlog; i >= 0; --i)
        {
            if (p->child[0]->size >= k)//如果左边大，就走左边
                p = p->child[0];
            else
            {
                ans |= (1 << i);//如果左边小，说明这一位为1,
                k -= p->child[0]->size;//减去左边的个数（对应在平衡树就是减去小于的个数）
                p = p->child[1];
            }

            if (p == root)
                break;
        }

        return ans - maxn;//记得减去maxn，处理了负数
    }

    int get_rank(int x)//根据值获得排名，注意，获得的是小于本身的个数！
    {
        int ans = 0;
        node *p = root;

        for (int i = maxlog; i >= 0; --i)
        {
            if ((x >> i) & 1)//为1，加上左子树的个数
            {
                ans += p->child[0]->size;
                p = p->child[1];
            }
            else
            {
                p = p->child[0];
            }

            if (p == root)
                break;
        }

        return ans;
    }

    int get_pre(int x)
    {
        return get_val(get_rank(x));//
    }

    int get_next(int x)
    {
        return get_val(get_rank(x + 1) + 1);//get_rank(x+1)获得了小于等于本身的个数，再加1，就是第一个大于本身的数。
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    Tire01 it;
    int n;
    cin >> n;

    while (n--)
    {
        int op, x;
        cin >> op >> x;

        x += maxn;

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
            cout << it.get_rank(x) + 1 << '\n';//注意一定要加1，因为获得的是小于本身的个数
        }
        else if (op == 4)
        {
            cout << it.get_val(x - maxn) << '\n';
        }
        else if (op == 5)
        {
            cout << it.get_pre(x) << '\n';
        }
        else if (op == 6)
        {
            cout << it.get_next(x) << '\n';
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
    cout << endl;
    system("pause");
    return 0;
}