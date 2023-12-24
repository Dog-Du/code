#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

class Solution {
public:
    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};

    void dfs(int x,int y,int &n,int &m,vector<vector<char>>&grid)
    {
        grid[x][y]='0';
        for(int i=0,nx,ny;i<4;++i)
        {
            nx=x+dx[i],ny=y+dy[i];
            if(nx<0||nx>=n||ny<0||ny>=m||grid[nx][ny]=='0')continue;
            dfs(nx,ny,n,m,grid);
        }
    }

    int numIslands(vector<vector<char>>& grid) {
        int cnt=0;
        int n=grid.size();
        int m=grid.front().size();

        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
                if(grid[i][j]=='1')
                {
                    ++cnt;
                    dfs(i,j,n,m,grid);
                }
        return cnt;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    


    cout<<endl;
    system("pause");
    return 0;
}
