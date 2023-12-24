#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

class Solution
{
public:
    int n, m;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    void dfs(int x, int y, vector<vector<char>> &board)
    {
        board[x][y] = '1';
        for (int i = 0, nx, ny; i < 4; ++i)
        {
            nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || board[nx][ny] != 'O')
                continue;
            dfs(nx, ny, board);
        }
    }

    void solve(vector<vector<char>> &board)
    {
        n = board.size(), m = board.front().size();

        for (int i = 0; i < n; ++i)
        {
            if (board[i][0] == 'O')
                dfs(i, 0, board);
            if (board[i][m - 1] == 'O')
                dfs(i, m - 1, board);
        }

        for (int i = 0; i < m; ++i)
        {
            if (board[0][i] == 'O')
                dfs(0, i, board);
            if (board[n - 1][i] == 'O')
                dfs(n - 1, i, board);
        }
        
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
            {
                if (board[i][j] == '1')
                    board[i][j] = 'O';
                else if (board[i][j] == 'O')
                    board[i][j] = 'X';
            }
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    vector<vector<string>> t={{"X","X","X","X"},{"X","O","O","X"},{"X","X","O","X"},{"X","O","X","X"}};
    vector<vector<char>> vec;

    for(int i=0;i<t.size();++i)
    {
        vec.push_back({});
        for(int j=0;j<t[i].size();++j)
            vec[i].push_back(t[i][j].front());
    }


    for(auto&it:vec)
    {
        for(auto&iter:it)
            cout<<iter;
        cout<<endl;
    }

    Solution one;

    one.solve(vec);

    for(auto&it:vec)
    {
        for(auto&iter:it)
            cout<<iter;
        cout<<endl;
    }
    cout << endl;
    system("pause");
    return 0;
}
