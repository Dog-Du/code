#include <iostream>
#include <cstring>

using namespace std;

const int maxn = 1e2 + 10;
int n;
char graph[maxn][maxn];
int col[maxn], dg[maxn], rdg[maxn];

void dfs(int row = 1)
{
    if (row > n)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
                cout << graph[i][j];
            cout << '\n';
        }

        cout << endl;

        return;
    }

    for (int i = 1; i <= n; ++i)
    {
        if (!col[i] && !dg[i + row] && !rdg[n - i + row])
        {
            col[i] = dg[i + row] = rdg[n - i + row] = 1;
            graph[row][i] = 'Q';
            dfs(row + 1);
            graph[row][i] = '.';
            col[i] = dg[i + row] = rdg[n - i + row] = 0;
        }
    }
}

int main()
{
    // cin>>n;
    n = 8;
    memset(graph, '.', sizeof graph);

    dfs();

    cout << endl;
    system("pause");
    return 0;
}
