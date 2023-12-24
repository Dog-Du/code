#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define ll long long

using namespace std;

class Solution {
private:
    int n;

    struct node{
        int now,step;
    };

    pair<int,int> getpos(int id)
    {
        pair<int,int> ans;
        ans.first=(id-1)/n;
        ans.second=(id-1)%n;
        if(ans.first%2==1)ans.second=n-1-ans.second;
        ans.first=n-1-ans.first;
        return ans;
    }

public:
    int snakesAndLadders(vector<vector<int>>& board) {
        queue<node> que;
        n=board.size();

        que.push({1,0});
        node j;
        pair<int,int> t;

        while(!que.empty())
        {
            j=que.front();
            que.pop();

            for(int i=1,x,y,next;i<=6;++i)
            {
                next=j.now+i;

                if(next>n*n)break;

                t=getpos(next);

                if(board[t.first][t.second]>0){
                    next=board[t.first][t.second];
                }

                if(next==n*n)return j.step+1;

                if(board[t.first][t.second]!=-2){
                    board[t.first][t.second]=-2;
                    que.push({next,j.step+1});
                }
            }
        }

        return -1;
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
