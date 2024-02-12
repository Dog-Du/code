#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <numeric>
#include <deque>

#define ll long long

using namespace std;

//动态规划
class Solution {
public:
    int stoneGameVII(vector<int>& stones) {
        int n=stones.size();
        vector<vector<int>> dp(n,vector<int>(n,0));
        //dp[i][j]:表示剩下的石头堆为 i 到 j 时，当前玩家与另一个玩家得分差的最大值，当前玩家不一定是先手Alice.
        //最大得分差 可以理解为此次操作之后，A 所收获的价值 - 下次B 比A的得分差的最大值。
        vector<int> sum(n+1,0);

        for(int i=0;i<n;++i)
            sum[i+1]=sum[i]+stones[i];
        
        auto get_sum=[&sum](int l,int r)->int
        {
            return sum[r+1]-sum[l];
        };

        for(int i=n-1;i>=0;--i)
        {
            for(int j=i+1;j<n;++j)
            {
                dp[i][j]=max(get_sum(i+1,j)-dp[i+1][j],get_sum(i,j-1)-dp[i][j-1]);
            }
        }

        return dp[0][n-1];
    }
};

//贪心
class Solution {
public:
    int stoneGameVII(vector<int>& stones) {
        int sum=accumulate(stones.begin(),stones.end(),0);
        deque<int> q(stones.begin(),stones.end());

        int alice=0,bob=0;

        bool flag=true;

        while(!q.empty())
        {
            if(q.front()<q.back())
            {
                sum-=q.front();
                alice+=(flag?sum:0);
                bob+=(!flag?sum:0);
                q.pop_front();
            }
            else
            {
                sum-=q.back();
                alice+=(flag?sum:0);
                bob+=(!flag?sum:0);
                q.pop_back();
            }
            flag=!flag;
        }

        return alice-bob;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

#ifdef LOCAL
    clock_t c1 = clock();
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif

//-------------------------------------------------

    


//-------------------------------------------------

#ifdef LOCAL
    cout << "\nTime Used: \n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
