#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

class Solution {
private:
    int n,m;
    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};

    bool dfs(int x,int y,int now,string&s,vector<vector<char>>&board)
    {
        if(now==s.size())
            return true;
        
        char ch=board[x][y];
        board[x][y]='?';

        for(int i=0,nx,ny;i<4;++i)
        {
            nx=x+dx[i],ny=y+dy[i];
            if(nx<0||nx>=n||ny<0||ny>=m||
                board[nx][ny]!=s[now])continue;

            if(dfs(nx,ny,now+1,s,board))
                return true;
        }

        board[x][y]=ch;
        return false;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        n=board.size(),m=board.front().size();

        for(int i=0,j;i<n;++i)
            for(j=0;j<m;++j)
                if(board[i][j]==word.front())
                    if(dfs(i,j,1,word,board))return true;

        return false;
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
