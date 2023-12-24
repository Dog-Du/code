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
    int minSubArrayLen(int target, vector<int>& nums) {
        int sum=0,n=nums.size(),ans=12345678;

        for(int l=0,r=0;r<n;++r)
        {
            sum+=nums[r];

            while(sum>=target)
            {
                ans=min(ans,r-l+1);
                sum-=nums[l++];
            }
        }

        return ans==12345678?0:ans;
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
