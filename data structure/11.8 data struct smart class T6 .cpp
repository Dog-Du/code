#include "10.31 create_graph linjiebiao .cpp"

bool dfs(int x, int &y, int fa, Graph &it, bool used[])
{
    for (ArcNode *j = it.getArc(x); j != nullptr; j = j->next)
    {
        if (used[j->to])
            continue;
        if (fa != y && j->to == y)
            return true;
        used[j->to] = 1;
        if (dfs(j->to, y, x, it, used))
            return true;
        used[j->to] = 0;
    }

    return false;
}

bool check(int x, Graph &it)
{
    bool used[it.getvnum() + 1] = {0};

    return dfs(x, x, x, it, used);
}

void solve()
{
    int n, m, x;
    cin >> n >> m >> x;
    Graph it(n);

    while (m--)
    {
        int x, y;
        cin >> x >> y;
        it.addedge(x, y, 0);
        it.addedge(y, x, 0);
    }

    if (check(x, it))
    {
        cout << "yes" << endl
             << endl;
    }
    else
    {
        cout << "no" << endl
             << endl;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    cout << endl;
    system("pause");
    return 0;
}
