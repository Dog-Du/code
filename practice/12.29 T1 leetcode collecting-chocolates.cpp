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

    //O(n^2)解法：
    //思路：轮换n次，那么对于 nums[i] 来说它的贡献变成了 min({nums[i],nums[i+1]....,nums[i+n]}) 
    //那么先处理从0到n-1次的轮转耗费，记作cost[]，然后枚举轮转次数
    //对于 节点 i 考虑向右找 n-1 个，然后依次存入对应的轮转耗费，最后输出轮转最少的耗费；
    long long minCost(vector<int>& nums, int x) {
        long long ans=1e10,n=nums.size();
        vector<long long> cost(n);

        for(long long i=0;i<n;++i)
            cost[i]=i*x;
        
        for(int i=0;i<n;++i)//枚举左端点
        {
            int minn=nums[i];
            for(int j=0;j<i+n;++j)//枚举右端点
            {
                minn=min(minn,nums[j%n]);
                cost[j-i]+=minn;//对应的轮转次数
            }
        }

        return *min_element(cost.begin(),cost.end());
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
