#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>

#define ll long long

using namespace std;

class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int n=nums.size();
        vector<int> dp(n,int(-1e9));
        deque<pair<int,int>> que;
        dp[0]=nums[0];
        que.push_back({dp[0],0});
        
        for(int i=1;i<n;++i)
        {
            while(!que.empty()&&que.front().second+k<i)
                que.pop_front();
            
            dp[i]=que.front().first+nums[i];

            while(!que.empty()&&dp[i]>que.back().first)
                que.pop_back();

            que.push_back({dp[i],i});
        }

        return dp.back();
    }
};

//动态规划，时间复杂度： O(n*k)
class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int n=nums.size();
        vector<int> dp(n,int(-1e9));
        dp[0]=nums[0];

        k%=n;

        for(int i=0;i<n;++i)
        {
            for(int j=i+1;j<=i+k&&j<n;++j)
            {
                dp[j]=max(dp[j],dp[i]+nums[j]);
            }
        }

        return dp.back();
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
