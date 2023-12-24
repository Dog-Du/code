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

    bool check(int x,int y,char ch,vector<vector<char>> &board)
    {
        for(int i=0;i<9;++i)
            if(board[x][i]==ch)return false;
        
        for(int i=0;i<9;++i)
            if(board[i][y]==ch)return false;
        
        int xx=(x/3)*3,yy=(y/3)*3;

        for(int i=xx;i<xx+3;++i)
            for(int j=yy;j<yy+3;++j)
                if(board[i][j]==ch)return false;

        return true;
    }

    bool dfs(int x,int y,vector<vector<char>>&board)
    {
        //妈的隔壁，这个if坑死我了
        if(x>8)return true;
        else if(y>8){ if(dfs(x+1,0,board)) return true;}
        else if(board[x][y]!='.') {if(dfs(x,y+1,board)) return true;}
        else
        {

                for(char ch='1';ch<='9';++ch)
                {
                    if(check(x,y,ch,board))
                    {
                       board[x][y]=ch;
                       if(dfs(x,y+1,board))return true;
                     board[x][y]='.';
                   }
                 }   
             
        }

        return false;
    }

   void solveSudoku(vector<vector<char>>& board) {
         dfs(0,0,board);
    }   
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    Solution one;
    vector<vector<char>> vec(9);

    for(int i=0;i<9;++i)
    {
        for(int j=0;j<9;++j)
        {
            char ch;
            cin>>ch;
            vec[i].push_back(ch);
        }
    }

    one.solveSudoku(vec);

    cout<<endl<<endl;
    for(int i=0;i<9;++i)
    {
        for(int j=0;j<9;++j)
            cout<<vec[i][j];
        cout<<endl;
    }

    cout<<endl;
    system("pause");
    return 0;
}
