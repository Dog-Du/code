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
    int n,m;

    //1表示存活，0表示死亡
    //刷新之后，1表示原来存活之后存活，0表示原来死亡之后死亡
    //2表示原来死亡之后存活，-1表示原来存活之后死亡

    int check(vector<vector<int>> & board,int x,int y)
    {
        int cnt=0;
        int dx[]={-1,-1,-1,0,0,1,1,1};
        int dy[]={-1,0,1,-1,1,-1,0,1};

        for(int i=0,nx,ny;i<8;++i)
        {
            nx=x+dx[i],ny=y+dy[i];

            if(nx<0||nx>=n||ny<0||ny>=m)continue;

            if(board[nx][ny]==1||board[nx][ny]==-1)++cnt;
        }

        return cnt;
    }

    void gameOfLife(vector<vector<int>>& board) {
        n=board.size(),m=board.front().size();

        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
            {
                int cnt=check(board,i,j);
                
                if(board[i][j]==1&&cnt<2)board[i][j]=-1;
                else if(board[i][j]==1&&(cnt==2||cnt==3))board[i][j]=1;
                else if(board[i][j]==1&&cnt>3)board[i][j]=-1;
                else if(board[i][j]==0&&cnt==3)board[i][j]=2;
            }
        
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
                if(board[i][j]>0)board[i][j]=1;
                else board[i][j]=0;
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
