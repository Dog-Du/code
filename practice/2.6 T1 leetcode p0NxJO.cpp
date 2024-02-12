#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <cstring>
#include <queue>
#include <numeric>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;


//反悔贪心：
//首先，如果数组之和小于0，无解，直接返回-1
//遍历一遍数组，cur加上数字，如果数字小于0，则加入小根堆
//如果cur小于1，这个时候反悔，减去那个最大的负数，ans加1
//最后返回ans
class Solution{
public:
    int magicTower(vector<int>& nums) {
        if(accumulate(nums.begin(),nums.end(),0LL)<0)
            return -1;
        
        priority_queue<int,vector<int>,greater<int>> que;
        int ans=0;
        long long cur=1;

        for(const auto&it : nums)
        {
            cur+=it;

            if(it<0)
                que.push(it);

            if(cur<1)
            {
                cur-=que.top();
                que.pop();
                ++ans;
            }
        }

        return ans;
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
