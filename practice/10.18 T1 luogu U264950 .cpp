#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

// 因为查询的时候总是从前向后查询，不是随机区间查询，所以可以使用权值线段树，查询一个就删除一个就好了
const int maxn = 1e6 + 10;

struct node
{
    int id;
    ll x;

    bool operator<(const node &it) const
    {
        return x < it.x;
    }
};

int t[maxn << 2];
int n;
vector<ll> res;
vector<node> a;

inline void modify(int x, int l, int r, int id, int k)
{
    if (l == r)
    {
        t[x] += k;
        return;
    }

    int mid = l + r >> 1;

    if (mid >= id)
        modify(x << 1, l, mid, id, k);
    else
        modify(x << 1 | 1, mid + 1, r, id, k);

    t[x] = t[x << 1] + t[x << 1 | 1];
}

inline int query(int x, int l, int r, int id, int cnt)
{
    if (l == r)
    {
        --t[x];
        return cnt;
    }

    int mid = l + r >> 1, ans;

    if (mid >= id)
        ans = query(x << 1, l, mid, id, cnt);
    else
        ans = query(x << 1 | 1, mid + 1, r, id, cnt - t[x << 1]);

    t[x] = t[x << 1] + t[x << 1 | 1];
    return ans;
}

inline void build(int x, int l, int r)
{
    if (l == r)
    {
        t[x] = 1;
        return;
    }
    int mid = l + r >> 1;
    build(x << 1, l, mid);
    build(x << 1 | 1, mid + 1, r);
    t[x] = t[x << 1] + t[x << 1 | 1];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;

    a.resize(n + 1);
    res.resize(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i].x;
        a[i].id = i;
    }

    stable_sort(a.begin() + 1, a.end());

    build(1, 1, n);

    ll sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        sum += a[i].x;

        // 如果填a[i].id+1会找到最右边的，导致最后的n会出现1，然后t2会少1，然后得到结果少1
        int t1 = query(1, 1, n, a[i].id, t[1]) - 1;
        int t2 = n - i - t1;
        // cout<<t1<<' '<<t2<<endl;
        //  答案等于前面所有的小于的+本身 + 本身-1 * 在后面的 + 本身* 在前面的
        res[a[i].id] = sum + (a[i].x - 1) * t1 + a[i].x * t2;

        // modify(1, 1, n, a[i].id, -1);
    }

    for (int i = 1; i <= n; ++i)
        cout << res[i] << '\n';

    cout << endl;
    system("pause");
    return 0;
}

// 主席树，因为被卡MLE过不了
//  #include <iostream>
//  #include <cmath>
//  #include <string>
//  #include <cstring>
//  #include <vector>
//  #include <algorithm>
//  #define us unsigned short
//  #define ll long long

// using namespace std;

// const int maxn = 1e6 + 10;

// struct node
// {
//     int id;
//     ll x;

//     bool operator<(const node &it) const
//     {
//         return x < it.x;
//     }
// };

// struct Tree
// {
//     int l, r;
//     int cnt;
// };

// vector<Tree> t;

// int n, cnt = 0;
// vector<ll> res;
// vector<int> root;
// vector<node> a;

// inline void modify(int &x, int l, int r, int &id)
// {
//     t[++cnt] = t[x];
//     x = cnt;
//     t[x].cnt++;

//     if (l == r)
//         return;

//     int mid = l + r >> 1;

//     if (mid >= id)
//         modify(t[x].l, l, mid, id);
//     else
//         modify(t[x].r, mid + 1, r, id);
// }

// inline int query(int L, int R, int l, int r, int id, int cnt) // 求后面的大于等于id的个数
// {
//     if (l == r)
//         return cnt;

//     int mid = l + r >> 1;

//     if (mid >= id)
//         return query(t[L].l, t[R].l, l, mid, id, cnt);

//     else
//         // 向右子树走，减去左子树的部分
//         return query(t[L].r, t[R].r, mid + 1, r, id, cnt - (t[t[R].l].cnt - t[t[L].l].cnt));
// }

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0), cout.tie(0);

//     cin >> n;

//     a.resize(n + 1);
//     t.resize(n * 16);
//     root.resize(n + 1);
//     res.resize(n + 1);

//     for (int i = 1; i <= n; ++i)
//     {
//         cin >> a[i].x;
//         a[i].id = i;
//     }

//     stable_sort(a.begin() + 1, a.end());

//     for (int i = 1; i <= n; ++i)
//     {
//         root[i] = root[i - 1];

//         modify(root[i], 1, n, a[i].id);
//     }

//     ll sum = 0;
//     for (int i = 1; i <= n; ++i)
//     {
//         sum += a[i].x;

//         // t1是排序之后在i后面的，且id号大于a[i].id+1 的个数
//         // t2则是小于的个数
//         int t1 = query(root[i], root[n], 1, n, a[i].id + 1, n - i);
//         int t2 = n - i - t1;

//         // 答案等于前面所有的小于的+本身 + 本身-1 * 在后面的 + 本身* 在前面的
//         res[a[i].id] = sum + (a[i].x - 1) * t1 + a[i].x * t2;
//     }

//     for (int i = 1; i <= n; ++i)
//         cout << res[i] << '\n';

//     cout << endl;
//     system("pause");
//     return 0;
// }

// // 线段树，被卡成O(N^2)了
//  struct node{
//      int maxn,minn,sum;
//      node*l,*r;
//  }*t;

// const int N=1e6+10;

// int a[N];
// int n;

// inline void pushup(node*&root)
// {
//     root->minn=min(root->l->minn,root->r->minn);
//     root->maxn=max(root->l->maxn,root->r->maxn);
//     root->sum=root->l->sum+root->r->sum;
//     return;
// }

// inline void build(node*&root,int l,int r)
// {
//     root=new node;
//     root->l=NULL,root->r=NULL;

//     if(l==r)
//     {
//         root->maxn=root->minn=root->sum=a[l];
//         return;
//     }

//     int mid=l+r>>1;

//     build(root->l,l,mid);
//     build(root->r,mid+1,r);

//     pushup(root);
// }

// inline int query1(node*&root,int l,int r,int L,int R,int key)
// {
//     if(l>=L&&r<=R&&root->minn>=key)
//     {
//         return key*(r-l+1);
//     }

//     if(l>=L&&r<=R&&root->maxn<=key)
//     {
//         return root->sum;
//     }

//     int mid=l+r>>1;
//     int ans=0;

//     if(mid>=L)ans+=query1(root->l,l,mid,L,R,key);
//     if(mid<R)ans+=query1(root->r,mid+1,r,L,R,key);

//     return ans;
// }

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0),cout.tie(0);

//     cin>>n;

//     for(int i=1;i<=n;++i)
//         cin>>a[i];

//     build(t,1,n);

//     for(int i=1;i<=n;++i)
//     {
//         int ans=0;

//         if(i>1)
//             ans+=query1(t,1,n,1,i-1,a[i]);

//         if(i<n)
//             ans+=query1(t,1,n,i+1,n,a[i]-1);

//         cout<<ans+a[i]<<'\n';
//     }

//     cout<<endl;
//     system("pause");
//     return 0;
// }
