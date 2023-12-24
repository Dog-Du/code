#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define ll long long

using namespace std;

const int maxn = 1e3 + 10;

struct ArcNode
{ // 边
    int w, to;
    ArcNode *next;
    ArcNode()
    {
        w = 0, to = 0;
        next = nullptr;
    }
};

struct VNode
{ // 点
    int data;
    ArcNode *firarc;
    VNode()
    {
        data = 0;
        firarc = nullptr;
    }
};

class Graph
{ // 邻接表存图，不能修改点的个数....
private:
    int vnum, arcnum;
    VNode *vert;

public:
    int getvnum()
    {
        return vnum;
    }

    int getarcnum()
    {
        return arcnum;
    }
    ArcNode *getArc(int x)
    {
        return vert[x].firarc;
    }

    Graph(int x)
    {
        vnum = x;
        vert = new VNode[x + 1];
        arcnum = 0;
    }
    ~Graph()
    {
        ArcNode *temp = nullptr;
        for (int i = 1; i <= vnum; ++i)
        {
            for (ArcNode *j = getArc(i); j != nullptr; j = temp)
            {
                temp = j->next;
                delete j;
            }
        }
        delete[] vert;
    }

    void addedge(int x, int y, int w)
    {
        ArcNode *p = new ArcNode;
        p->next = vert[x].firarc;
        p->w = w;
        p->to = y;

        vert[x].firarc = p;
        ++arcnum;
    }
};

class BingChaJi
{
private:
    int n;
    int *pre;

public:
    BingChaJi(int x)
    {
        n = x;
        pre = new int[x + 1];
        for (int i = 1; i <= n; ++i)
            pre[i] = i;
    }
    ~BingChaJi()
    {
        delete[] pre;
    }

    int find(int x)
    {
        return pre[x] == x ? x : pre[x] = find(pre[x]);
    }

    void Union(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        pre[x] = y;
    }

    bool isSame(int x, int y)
    {
        return find(x) == find(y);
    }
};

int prim(Graph &school) //增点法 O(nlogn + e)
{
    int n = school.getvnum();
    if (n == 0)
        return -1;

    struct node
    {
        int id, w;
        bool operator<(const node &it) const
        {
            return w > it.w;
        }
    };

    priority_queue<node> que;

    int dist[n + 1];

    for (int i = 1; i <= n; ++i)
        dist[i] = 1e9 + 10;

    dist[1] = 0;
    int cnt = 0, sum = 0;
    que.push({1, 0});

    while (!que.empty())
    {
        int j = que.top().id, w = que.top().w;
        que.pop();
        if (dist[j] == -1)
            continue;
        dist[j] = -1;
        sum += w;
        ++cnt;

        for (ArcNode *k = school.getArc(j); k != nullptr; k = k->next)
        {
            if (dist[k->to] != -1 && dist[k->to] > k->w)
            {
                dist[k->to] = k->w;
                que.push({k->to, k->w});
            }
        }
    }

    if (cnt < n)
        return -1;
    return sum;
}

int krusal(Graph &school) //增边法 O(eloge + n)
{
    int n = school.getvnum(), m = school.getarcnum();

    struct node
    {
        int from, to, w;
        bool operator<(const node &it) const
        {
            return w < it.w;
        }
    };

    vector<node> edge;
    BingChaJi it(n);
    int cnt = 0, sum = 0;

    for (int i = 1; i <= n; ++i)
        for (ArcNode *j = school.getArc(i); j != nullptr; j = j->next)
            edge.push_back({i, j->to, j->w});

    sort(edge.begin(), edge.end());

    for (const auto &iter : edge)
    {
        if (it.isSame(iter.from, iter.to))
            continue;
        it.Union(iter.from, iter.to);
        ++cnt;
        sum += iter.w;
    }

    if (cnt < n - 1)
        return -1;

    return sum;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    Graph school(n);

    while (m--)
    {
        int x, y, w;
        cin >> x >> y >> w;

        school.addedge(x, y, w);
        school.addedge(y, x, w);
    }

    int ans1 = prim(school), ans2 = krusal(school);
    cout << "prim : " << ans1 << " ||| "
         << "krusal : " << ans2 << endl
         << endl;
}

int main()
{
    int t;
    cout << "input test times : ";
    cin >> t;

    while (t--)
    {
        solve();
    }

    cout << endl;
    system("pause");
    return 0;
}
