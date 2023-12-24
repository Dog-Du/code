#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

//最大值等于 max(maxSum,total-minsum) 最大数组和 和 总数减去最小数组和

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int total=0,maxsum=nums.front(),curmax=0,minsum=nums.front(),curmin=0;

        for(auto&it:nums)
        {
            curmax=max(curmax+it,it);
            maxsum=max(maxsum,curmax);
            curmin=min(curmin+it,it);
            minsum=min(minsum,curmin);
            total+=it;
        }
        return maxsum>0?max(maxsum,total-minsum):maxsum;
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
