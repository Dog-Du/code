#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <cstring>
#include <vector>
#include <numeric>
#include <algorithm>

#define ll long long

using namespace std;


class Solution {
public:
    int minimumTime(vector<int>& nums1, vector<int>& nums2, int x) {
        int n=nums1.size();
        vector<int> pos(n);

        for(int i=0;i<n;++i)
            pos[i]=i;
        
        sort(pos.begin(),pos.end(),[&nums2](int i,int j)->bool
                        {return nums2[i]<nums2[j];});
        
        vector<int> dp(n+1);//前i秒所减少的最大量。
        // 对于一个点 i  在 j 时间减少量为 nums1[i] + j*nums2[i];
        //根据排序不等式：正序乘之和为最大
        //(若： a1<=a2<=***<=an ,b1<=b2<=***<=bn 则有 a1*b1+a2*b2+****+an*bn >= 其他)
        //取等条件为 ai=aj且bi=bj 其中 j=n-i+1
        //又因为减少量分为nums1[i],nums2[i]两部分，其中nums1[i]不受时间影响
        //

        for(int i=0;i<n;++i)
        {
            int a=nums1[pos[i]],b=nums2[pos[i]];

            for(int j=i+1;j>0;--j)
                dp[j]=max(dp[j],dp[j-1]+a+b*j);
        }
        
        int s1=accumulate(nums1.begin(),nums1.end(),0);
        int s2=accumulate(nums2.begin(),nums2.end(),0);

        for(int t=0;t<=n;++t)
            if(s1+s2*t-dp[t]<=x)
                return t;
        
        return -1;
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

    vector<int> vec1={4,4,9,10},vec2={4,4,1,3};
    Solution one;
    one.minimumTime(vec1,vec2,16);


//-------------------------------------------------

#ifdef LOCAL
    cout << "\nTime Used: \n" << clock() - c1 << " ms" << endl;
#endif

    //system("pause");
    return 0;
}
