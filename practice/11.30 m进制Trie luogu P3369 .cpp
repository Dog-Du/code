#include <iostream>
#include <cmath>
using namespace std;


//m进制Trie，和01Trie思想是一致的，
//先获得maxn，而且maxn必须是m的幂数
const int m=35,N=1e7+10, maxlog=ceil(log(N)/log(m)),maxn=pow(m,maxlog);

class m_Tire
{
private:
    struct node
    {
        node *child[m];
        int size;
        node(node *p)
        {
            for(int i=0;i<m;++i)child[i]=p;
            size = 0;
        }
    } *root;

    void clear(node*now)
    {
        if(now==root)return;
        
        for(int i=0;i<m;++i)
            clear(now->child[i]);
        delete now;
    }

public:

    void clear()
    {
        for(int i=0;i<m;++i)
        {
            clear(root->child[i]);
            root->child[i]=root;
        }
    }

    ~m_Tire()
    {
        clear();
        delete root;
    }

    m_Tire()//设置头结点root，让所有空节点都指向root
    {
        root = new node(nullptr);
        for(int i=0;i<m;++i)
            root->child[i]=root;
    }

    void insert(int x)
    {
        node *p = root;

        for (int power=maxn,t; power; power/=m)
        {
            t = (x / power)  % m;//获得这一位的数字，即余数

            if (p->child[t] == root)
                p->child[t] = new node(root);//如空，则新建

            p = p->child[t];
            ++p->size;
        }
    }

    void erase(int x)//删除则更简单，直接沿路删除即可，因为不需要释放空间，
    {
        node *p = root;

        for (int power=maxn, t; power; power/=m)
        {
            t = (x /power) % m;
            p = p->child[t];
            --p->size;
        }
    }

    int get_val(int k)//根据排名获得值
    {

        node *p = root;
        int ans = 0;

        for (int power=maxn,j,sum; power; power/=m)
        {
            for(j=0,sum=0;j<m&&sum<k;++j)//获得第一位sum大于等于地方
                sum+=p->child[j]->size;

            //if(sum>=k)
           // {

            k-=(sum-p->child[j-1]->size);//注意一定要减去小于本身的那些数的个数，这个时候j指向的是第一个大于等于，所以把左边的全部剪掉
            p=p->child[j-1];
            ans+=(j-1)*power;//注意细微的差别，这里也要加上

            //}

            //这部分是不被需要的，因为sum一定大于等于k，这是上面for循环所保证的。
            // else
            // {
            //     k-=sum;
            //     p=p->child[j];
            //     ans+=j*power;
            // }

            if (p == root)
                break;
        }

        return ans - maxn;//记得减去maxn，处理了负数
    }

    int get_rank(int x)//根据值获得排名，注意，获得的是小于本身的个数！
    {
        int ans = 0;
        node *p = root;

        for (int power=maxn,t,sum,i; power; power/=m)
        {
            for(i=0,sum=0,t=(x/power)%m;i<t;++i)
                sum+=p->child[i]->size;
            
            ans+=sum;
            p=p->child[t];

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

    m_Tire it;
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


    cout << endl;
    system("pause");
    return 0;
}