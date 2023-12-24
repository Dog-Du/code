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
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;

        sort(nums.begin(),nums.end());

        for(int i=0,n=nums.size();i<n;++i)
        {
            if(nums[i]>0)break;
            if(i>0&&nums[i]==nums[i-1])continue;//不能是i==i+1因为[0.0,0]会错过

            int j=i+1,k=n-1;

            while(j<k)
            {
                if(nums[i]+nums[j]+nums[k]>0)--k;
                else if(nums[i]+nums[j]+nums[k]<0)++j;
                else
                {
                    ans.push_back({nums[i],nums[j],nums[k]});

                    while(j<k&&nums[j+1]==nums[j])++j;
                    while(j<k&&nums[k-1]==nums[k])--k;
                    --k,++j;
                }
            }
        }

        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    Solution one;
    vector<int> vec={-1,0,1,2,-1,-4};

    one.threeSum(vec);


    cout<<endl;
    system("pause");
    return 0;
}
